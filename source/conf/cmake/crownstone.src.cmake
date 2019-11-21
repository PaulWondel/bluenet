# List of Crownstone specific code
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_Advertiser.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_Characteristic.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_CrownstoneManufacturer.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_Service.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_ServiceData.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_Softdevice.c")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_Stack.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_UUID.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/cfg/cs_Boards.c")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/common/cs_Handlers.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/common/cs_Types.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_ADC.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_COMP.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_PWM.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_RNG.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_Serial.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_Storage.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/drivers/cs_Timer.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/events/cs_Event.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/events/cs_EventDispatcher.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/presence/cs_PresenceCondition.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/presence/cs_PresencePredicate.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/presence/cs_PresenceHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/behaviour/cs_Behaviour.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/behaviour/cs_BehaviourHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/behaviour/cs_BehaviourStore.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_BackgroundAdvHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_CommandAdvHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_CommandHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_EncryptionHandler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_ExternalStates.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_FactoryReset.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_RecognizeSwitch.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_Scanner.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_Scheduler.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_Setup.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_TapToToggle.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_TemperatureGuard.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/protocol/cs_UartProtocol.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/protocol/mesh/cs_MeshModelPacketHelper.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/services/cs_CrownstoneService.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/services/cs_DeviceInformationService.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/services/cs_SetupService.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/storage/cs_State.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/structs/buffer/cs_CharacteristicBuffer.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/storage/cs_StateData.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/structs/cs_ScheduleEntriesAccessor.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/switch/cs_HwSwitch.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/switch/cs_SwSwitch.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/switch/cs_SwitchAggregator.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/third/optmed.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/third/SortMedian.cc")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/third/nrf/app_error_weak.c")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/time/cs_SystemTime.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/time/cs_TimeOfDay.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/util/cs_BleError.cpp")
#LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/util/cs_Error.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/util/cs_Hash.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/util/cs_Syscalls.c")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/util/cs_WireFormat.cpp")

LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_PowerSampling.cpp")
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/processing/cs_MultiSwitchHandler.cpp")

# should be only when creating iBeacon
LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/ble/cs_iBeacon.cpp")

IF (MESHING AND "${MESHING}" STRGREATER "0" AND BUILD_MESHING AND "${BUILD_MESHING}" STREQUAL "0")
	MESSAGE(FATAL_ERROR "Need to set BUILD_MESHING=1 if MESHING should be enabled!")
ENDIF()

IF (BUILD_MESHING)
	LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/mesh/cs_Mesh.cpp")
	LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/mesh/cs_MeshModel.cpp")
	LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/mesh/cs_MeshAdvertiser.cpp")
#	LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/protocol/mesh/cs_MeshMessageState.cpp")
#	LIST(APPEND FOLDER_SOURCE "${SOURCE_DIR}/protocol/mesh/cs_MeshMessageCounter.cpp")

	IF (NOT DEFINED MESH_SDK_DIR)
		MESSAGE(FATAL_ERROR "MESH_SDK_DIR is not defined!")
	ENDIF()

	IF(IS_DIRECTORY "${MESH_SDK_DIR}")
		MESSAGE(STATUS "Use directory ${MESH_SDK_DIR} for the mesh")
	ELSE()
		MESSAGE(FATAL_ERROR "Directory for the mesh, \"${MESH_SDK_DIR}\", does not exist!")
	ENDIF()
ENDIF()

