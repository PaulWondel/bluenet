# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gmprincep/gitfiles/bluenet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gmprincep/gitfiles/bluenet

# Utility rule file for bluenet.

# Include the progress variables for this target.
include CMakeFiles/bluenet.dir/progress.make

CMakeFiles/bluenet: CMakeFiles/bluenet-complete


CMakeFiles/bluenet-complete: default/stamp/bluenet-install
CMakeFiles/bluenet-complete: default/stamp/bluenet-mkdir
CMakeFiles/bluenet-complete: default/stamp/bluenet-download
CMakeFiles/bluenet-complete: default/stamp/bluenet-update
CMakeFiles/bluenet-complete: default/stamp/bluenet-patch
CMakeFiles/bluenet-complete: default/stamp/bluenet-configure
CMakeFiles/bluenet-complete: default/stamp/bluenet-build
CMakeFiles/bluenet-complete: default/stamp/bluenet-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'bluenet'"
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/CMakeFiles
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/CMakeFiles/bluenet-complete
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-done

default/stamp/bluenet-install: default/stamp/bluenet-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'bluenet'"
	cd /home/gmprincep/gitfiles/bluenet/default && $(MAKE) install
	cd /home/gmprincep/gitfiles/bluenet/default && /usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-install

default/stamp/bluenet-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'bluenet'"
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/source
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/default
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/bin/default
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/tmp/default
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/default/stamp
	/usr/bin/cmake -E make_directory /home/gmprincep/gitfiles/bluenet/bluenet-prefix/src
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-mkdir

default/stamp/bluenet-download: default/stamp/bluenet-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'bluenet'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-download

default/stamp/bluenet-update: default/stamp/bluenet-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'bluenet'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-update

default/stamp/bluenet-patch: default/stamp/bluenet-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'bluenet'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-patch

default/stamp/bluenet-configure: tmp/default/bluenet-cfgcmd.txt
default/stamp/bluenet-configure: default/stamp/bluenet-update
default/stamp/bluenet-configure: default/stamp/bluenet-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'bluenet'"
	cd /home/gmprincep/gitfiles/bluenet/default && /usr/bin/cmake -DWORKSPACE_DIR:STRING=/home/gmprincep/gitfiles/bluenet -DCONFIG_DIR:STRING=config -DBOARD_TARGET:STRING=default -DDEFAULT_CONF_CMAKE_PATH:STRING=/home/gmprincep/gitfiles/bluenet/source/conf/cmake -DDEFAULT_MODULES_PATH:STRING=/home/gmprincep/gitfiles/bluenet/source/conf/cmake/modules -DCMAKE_BUILD_TYPE:STRING=Debug -DSOFTDEVICE_HEX_FILE:STRING=components/softdevice/s132/hex/s132_nrf52_6.1.1_softdevice.hex -DNRF5_DIR:STRING=/home/gmprincep/gitfiles/bluenet/tools/nrf5_sdk -DMESH_SDK_DIR:STRING=/home/gmprincep/gitfiles/bluenet/tools/mesh_sdk -DCOMPILER_PATH:STRING=/home/gmprincep/gitfiles/bluenet/tools/gcc_arm_none_eabi -DBLUETOOTH_NAME:STRING=Test -DFIRMWARE_VERSION:STRING=undefined -DBOOTLOADER_VERSION:STRING=undefined -DDEFAULT_HARDWARE_BOARD:STRING=ACR01B2C -DCHANGE_NAME_ON_RESET:STRING=0 -DMESHING:STRING=1 -DBUILD_MESHING:STRING=1 -DIBEACON:STRING=1 -DDEFAULT_ON:STRING=0 -DINTERVAL_SCANNER_ENABLED:STRING=0 -DPWM_ENABLE:STRING=1 -DBEACON_UUID:STRING=a643423e-e175-4af0-a2e4-31e32f729a8a -DBEACON_MAJOR:STRING=0 -DBEACON_MINOR:STRING=0 -DBEACON_RSSI:STRING=0xC4 -DENCRYPTION:STRING=1 -DMAX_NUM_VS_SERVICES:STRING=2 -DCHAR_CONTROL:STRING=1 -DCHAR_CONFIGURATION:STRING=1 -DCHAR_STATE:STRING=1 -DMASTER_BUFFER_SIZE:STRING=300 -DSERIAL_VERBOSITY:STRING=SERIAL_DEBUG -DCS_SERIAL_ENABLED:STRING=0 -DCS_UART_BINARY_PROTOCOL_ENABLED:STRING=1 -DCS_SERIAL_NRF_LOG_ENABLED:STRING=0 -DCS_SERIAL_NRF_LOG_PIN_TX:STRING=6 -DNRF_SERIES:STRING=NRF52 -DTX_POWER:STRING=4 -DADVERTISEMENT_INTERVAL:STRING=160 -DMAX_CHIP_TEMP:STRING=75 -DBOOT_DELAY:STRING=400 -DSCAN_DURATION:STRING=2000 -DSCAN_BREAK_DURATION:STRING=7000 -DENABLE_RSSI_FOR_CONNECTION:STRING=1 -DCONNECTION_ALIVE_TIMEOUT:STRING=20000 -DCOMPILER_TYPE:STRING=arm-none-eabi- -DJLINK:STRING=/usr/bin/JLinkExe -DJLINK_GDB_SERVER:STRING=/usr/bin/JLinkGDBServer -DDEVICE:STRING=nRF52832_xxAA -DNRF51_USE_SOFTDEVICE:STRING=1 -DNORDIC_SDK_VERSION:STRING=15 -DSOFTDEVICE_NO_SEPARATE_UICR_SECTION:STRING=1 -DBOOTLOADER_START_ADDRESS:STRING=0x00076000 -DBOOTLOADER_LENGTH:STRING=0x8000 -DUICR_DFU_INDEX:STRING=0 -DUICR_BOARD_INDEX:STRING=1 -DHARDWARE_BOARD_ADDRESS:STRING=0x10001084 -DSOFTDEVICE_MAJOR:STRING=6 -DSOFTDEVICE_MINOR:STRING=1 -DSOFTDEVICE_SERIES:STRING=132 -DSOFTDEVICE:STRING=s132_nrf52_6.1.1 -DAPPLICATION_START_ADDRESS:STRING=0x00026000 -DAPPLICATION_LENGTH:STRING=0x5A000 -DATTR_TABLE_SIZE:STRING=0x500 -DRAM_R1_BASE:STRING=0x20002380 -DRAM_APPLICATION_AMOUNT:STRING=0xDC80 -DHEAP_SIZE:STRING=20000 -DBLUETOOTH_NAME:STRING=CRWN -DHARDWARE_BOARD:STRING=PCA10040 -DCS_SERIAL_ENABLED:STRING=SERIAL_ENABLE_RX_AND_TX -DSERIAL_VERBOSITY:STRING=SERIAL_DEBUG -DCS_UART_BINARY_PROTOCOL_ENABLED:STRING=0 -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/home/gmprincep/gitfiles/bluenet/source/arm.toolchain.cmake -DCMAKE_INSTALL_PREFIX:FILEPATH=/home/gmprincep/gitfiles/bluenet/bin/default -C/home/gmprincep/gitfiles/bluenet/tmp/default/bluenet-cache-Debug.cmake "-GUnix Makefiles" /home/gmprincep/gitfiles/bluenet/source
	cd /home/gmprincep/gitfiles/bluenet/default && /usr/bin/cmake -E touch /home/gmprincep/gitfiles/bluenet/default/stamp/bluenet-configure

default/stamp/bluenet-build: default/stamp/bluenet-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'bluenet'"
	cd /home/gmprincep/gitfiles/bluenet/default && $(MAKE)

bluenet: CMakeFiles/bluenet
bluenet: CMakeFiles/bluenet-complete
bluenet: default/stamp/bluenet-install
bluenet: default/stamp/bluenet-mkdir
bluenet: default/stamp/bluenet-download
bluenet: default/stamp/bluenet-update
bluenet: default/stamp/bluenet-patch
bluenet: default/stamp/bluenet-configure
bluenet: default/stamp/bluenet-build
bluenet: CMakeFiles/bluenet.dir/build.make

.PHONY : bluenet

# Rule to build all files generated by this target.
CMakeFiles/bluenet.dir/build: bluenet

.PHONY : CMakeFiles/bluenet.dir/build

CMakeFiles/bluenet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bluenet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bluenet.dir/clean

CMakeFiles/bluenet.dir/depend:
	cd /home/gmprincep/gitfiles/bluenet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet/CMakeFiles/bluenet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bluenet.dir/depend

