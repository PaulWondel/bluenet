/**
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: May 22, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include "processing/cs_ExternalStates.h"
#include "util/cs_BleError.h"
#include "util/cs_Utils.h"
//#include <cstring> // For calloc

/**
 * Interval at which the timeout counter is decreased.
 */
#define EXTERNAL_STATE_COUNT_INTERVAL_MS 1000
#define EXTERNAL_STATE_TIMEOUT_COUNT_START (EXTERNAL_STATE_TIMEOUT_MS / EXTERNAL_STATE_COUNT_INTERVAL_MS)

#if TICK_INTERVAL_MS > EXTERNAL_STATE_COUNT_INTERVAL_MS
#error "TICK_INTERVAL_MS must not be larger than EXTERNAL_STATE_COUNT_INTERVAL_MS"
#endif

#if EXTERNAL_STATE_TIMEOUT_COUNT_START == 0
#error "EXTERNAL_STATE_TIMEOUT_MS is too small, or EXTERNAL_STATE_COUNT_INTERVAL_MS is too large"
#endif

#if EXTERNAL_STATE_TIMEOUT_MS / EXTERNAL_STATE_COUNT_INTERVAL_MS > 0xFFFE
#error "EXTERNAL_STATE_TIMEOUT_MS / EXTERNAL_STATE_COUNT_INTERVAL_MS must fit in a uint16_t"
#endif

#define LOGExternalStatesDebug LOGnone

void ExternalStates::init() {
	_states = (cs_external_state_item_t*) calloc(EXTERNAL_STATE_LIST_COUNT, sizeof(cs_external_state_item_t));
	if (_states == NULL) {
		APP_ERROR_CHECK(ERR_NO_SPACE);
	}
}

void ExternalStates::receivedState(state_external_stone_t* state) {
	LOGExternalStatesDebug("received: id=%u flags=%u switch=%u power=%i ts=%u",
			state->data.extState.id,
			state->data.extState.flags,
			state->data.extState.switchState,
			state->data.extState.powerUsageReal,
			state->data.extState.partialTimestamp);

	stone_id_t id = service_data_encrypted_get_id(&(state->data));

	// Overwrite item with same id
	for (int i=0; i<EXTERNAL_STATE_LIST_COUNT; ++i) {
		if (_states[i].id == id) {
			addToList(i, id, state);
			return;
		}
	}

	// Else, write at oldest item
	uint16_t oldest = 0xFFFF;
	int oldestInd = 0;
	for (int i=0; i<EXTERNAL_STATE_LIST_COUNT; ++i) {
		if (_states[i].timeoutCount < oldest) {
			oldest = _states[i].timeoutCount;
			oldestInd = i;
		}
	}
	addToList(oldestInd, id, state);
}

void ExternalStates::removeFromList(stone_id_t id) {
	for (int i=0; i<EXTERNAL_STATE_LIST_COUNT; ++i) {
		if (_states[i].id == id) {
			_states[i].timeoutCount = 0;
			break;
		}
	}
}

void ExternalStates::addToList(int index, stone_id_t id, state_external_stone_t* state) {
	_states[index].id = id;
	_states[index].timeoutCount = EXTERNAL_STATE_TIMEOUT_COUNT_START;
	memcpy(&(_states[index].state), state, sizeof(*state));
	LOGExternalStatesDebug("added id=%u to ind=%u", id, index);
}

service_data_encrypted_t* ExternalStates::getNextState() {
	for (int i = _broadcastIndex; i < _broadcastIndex + EXTERNAL_STATE_LIST_COUNT; ++i) {
		int index = i % EXTERNAL_STATE_LIST_COUNT;
		if (_states[index].timeoutCount != 0) {
			_broadcastIndex = (index + 1) % EXTERNAL_STATE_LIST_COUNT;
			LOGExternalStatesDebug("picked ind=%u id=%u timeout=%u", index, _states[index].id, _states[index].timeoutCount);
			fixState(&(_states[index].state));
			return &(_states[index].state.data);
		}
	}
	return NULL;
}

/**
 * Fix the state:
 * - Set correct type (external)
 *   - This might mean we have to move some fields.
 * - Set correct validation
 * - Set correct rssi
 */
void ExternalStates::fixState(state_external_stone_t* state) {
	switch (state->data.type) {
	case SERVICE_DATA_TYPE_STATE:
		service_data_encrypted_convert_state_to_ext_state(&(state->data), state->rssi);
		break;
	case SERVICE_DATA_TYPE_ERROR:
		service_data_encrypted_convert_error_to_ext_error(&(state->data), state->rssi);
		break;
	case SERVICE_DATA_TYPE_EXT_STATE:
		break;
	case SERVICE_DATA_TYPE_EXT_ERROR:
		break;
	}
}

void ExternalStates::tick(TYPIFY(EVT_TICK) tickCount) {
	if (tickCount % (EXTERNAL_STATE_COUNT_INTERVAL_MS / TICK_INTERVAL_MS) == 0) {
		for (int i=0; i<EXTERNAL_STATE_LIST_COUNT; ++i) {
			if (_states[i].timeoutCount) {
				_states[i].timeoutCount--;
			}
		}
	}
}
