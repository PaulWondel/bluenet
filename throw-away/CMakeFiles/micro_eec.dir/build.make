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

# Utility rule file for micro_eec.

# Include the progress variables for this target.
include CMakeFiles/micro_eec.dir/progress.make

CMakeFiles/micro_eec:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Build micro-eec"
	cd /home/gmprincep/gitfiles/bluenet/tools/nrf5_sdk/external/micro-ecc && chmod u+x build_all.sh
	cd /home/gmprincep/gitfiles/bluenet/tools/nrf5_sdk/external/micro-ecc && /usr/bin/cmake -E env GNU_INSTALL_ROOT=/home/gmprincep/gitfiles/bluenet/tools/gcc_arm_none_eabi/bin/ MAKEFLAGS=-j1 ./build_all.sh

micro_eec: CMakeFiles/micro_eec
micro_eec: CMakeFiles/micro_eec.dir/build.make

.PHONY : micro_eec

# Rule to build all files generated by this target.
CMakeFiles/micro_eec.dir/build: micro_eec

.PHONY : CMakeFiles/micro_eec.dir/build

CMakeFiles/micro_eec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/micro_eec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/micro_eec.dir/clean

CMakeFiles/micro_eec.dir/depend:
	cd /home/gmprincep/gitfiles/bluenet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet/CMakeFiles/micro_eec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/micro_eec.dir/depend

