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

# Utility rule file for default.

# Include the progress variables for this target.
include CMakeFiles/default.dir/progress.make

CMakeFiles/default:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gmprincep/gitfiles/bluenet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Build application"
	cd /home/gmprincep/gitfiles/bluenet/default && make

default: CMakeFiles/default
default: CMakeFiles/default.dir/build.make

.PHONY : default

# Rule to build all files generated by this target.
CMakeFiles/default.dir/build: default

.PHONY : CMakeFiles/default.dir/build

CMakeFiles/default.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/default.dir/cmake_clean.cmake
.PHONY : CMakeFiles/default.dir/clean

CMakeFiles/default.dir/depend:
	cd /home/gmprincep/gitfiles/bluenet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet /home/gmprincep/gitfiles/bluenet/CMakeFiles/default.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/default.dir/depend

