# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/andy/Embedded-Miku/libsamplerate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andy/Embedded-Miku/libsamplerate/build_s

# Include any dependencies generated for this target.
include CMakeFiles/termination_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/termination_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/termination_test.dir/flags.make

CMakeFiles/termination_test.dir/tests/termination_test.c.o: CMakeFiles/termination_test.dir/flags.make
CMakeFiles/termination_test.dir/tests/termination_test.c.o: ../tests/termination_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andy/Embedded-Miku/libsamplerate/build_s/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/termination_test.dir/tests/termination_test.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/termination_test.dir/tests/termination_test.c.o   -c /home/andy/Embedded-Miku/libsamplerate/tests/termination_test.c

CMakeFiles/termination_test.dir/tests/termination_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/termination_test.dir/tests/termination_test.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andy/Embedded-Miku/libsamplerate/tests/termination_test.c > CMakeFiles/termination_test.dir/tests/termination_test.c.i

CMakeFiles/termination_test.dir/tests/termination_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/termination_test.dir/tests/termination_test.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andy/Embedded-Miku/libsamplerate/tests/termination_test.c -o CMakeFiles/termination_test.dir/tests/termination_test.c.s

CMakeFiles/termination_test.dir/tests/termination_test.c.o.requires:

.PHONY : CMakeFiles/termination_test.dir/tests/termination_test.c.o.requires

CMakeFiles/termination_test.dir/tests/termination_test.c.o.provides: CMakeFiles/termination_test.dir/tests/termination_test.c.o.requires
	$(MAKE) -f CMakeFiles/termination_test.dir/build.make CMakeFiles/termination_test.dir/tests/termination_test.c.o.provides.build
.PHONY : CMakeFiles/termination_test.dir/tests/termination_test.c.o.provides

CMakeFiles/termination_test.dir/tests/termination_test.c.o.provides.build: CMakeFiles/termination_test.dir/tests/termination_test.c.o


CMakeFiles/termination_test.dir/tests/util.c.o: CMakeFiles/termination_test.dir/flags.make
CMakeFiles/termination_test.dir/tests/util.c.o: ../tests/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andy/Embedded-Miku/libsamplerate/build_s/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/termination_test.dir/tests/util.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/termination_test.dir/tests/util.c.o   -c /home/andy/Embedded-Miku/libsamplerate/tests/util.c

CMakeFiles/termination_test.dir/tests/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/termination_test.dir/tests/util.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andy/Embedded-Miku/libsamplerate/tests/util.c > CMakeFiles/termination_test.dir/tests/util.c.i

CMakeFiles/termination_test.dir/tests/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/termination_test.dir/tests/util.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andy/Embedded-Miku/libsamplerate/tests/util.c -o CMakeFiles/termination_test.dir/tests/util.c.s

CMakeFiles/termination_test.dir/tests/util.c.o.requires:

.PHONY : CMakeFiles/termination_test.dir/tests/util.c.o.requires

CMakeFiles/termination_test.dir/tests/util.c.o.provides: CMakeFiles/termination_test.dir/tests/util.c.o.requires
	$(MAKE) -f CMakeFiles/termination_test.dir/build.make CMakeFiles/termination_test.dir/tests/util.c.o.provides.build
.PHONY : CMakeFiles/termination_test.dir/tests/util.c.o.provides

CMakeFiles/termination_test.dir/tests/util.c.o.provides.build: CMakeFiles/termination_test.dir/tests/util.c.o


CMakeFiles/termination_test.dir/tests/calc_snr.c.o: CMakeFiles/termination_test.dir/flags.make
CMakeFiles/termination_test.dir/tests/calc_snr.c.o: ../tests/calc_snr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andy/Embedded-Miku/libsamplerate/build_s/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/termination_test.dir/tests/calc_snr.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/termination_test.dir/tests/calc_snr.c.o   -c /home/andy/Embedded-Miku/libsamplerate/tests/calc_snr.c

CMakeFiles/termination_test.dir/tests/calc_snr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/termination_test.dir/tests/calc_snr.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andy/Embedded-Miku/libsamplerate/tests/calc_snr.c > CMakeFiles/termination_test.dir/tests/calc_snr.c.i

CMakeFiles/termination_test.dir/tests/calc_snr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/termination_test.dir/tests/calc_snr.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andy/Embedded-Miku/libsamplerate/tests/calc_snr.c -o CMakeFiles/termination_test.dir/tests/calc_snr.c.s

CMakeFiles/termination_test.dir/tests/calc_snr.c.o.requires:

.PHONY : CMakeFiles/termination_test.dir/tests/calc_snr.c.o.requires

CMakeFiles/termination_test.dir/tests/calc_snr.c.o.provides: CMakeFiles/termination_test.dir/tests/calc_snr.c.o.requires
	$(MAKE) -f CMakeFiles/termination_test.dir/build.make CMakeFiles/termination_test.dir/tests/calc_snr.c.o.provides.build
.PHONY : CMakeFiles/termination_test.dir/tests/calc_snr.c.o.provides

CMakeFiles/termination_test.dir/tests/calc_snr.c.o.provides.build: CMakeFiles/termination_test.dir/tests/calc_snr.c.o


# Object files for target termination_test
termination_test_OBJECTS = \
"CMakeFiles/termination_test.dir/tests/termination_test.c.o" \
"CMakeFiles/termination_test.dir/tests/util.c.o" \
"CMakeFiles/termination_test.dir/tests/calc_snr.c.o"

# External object files for target termination_test
termination_test_EXTERNAL_OBJECTS =

termination_test: CMakeFiles/termination_test.dir/tests/termination_test.c.o
termination_test: CMakeFiles/termination_test.dir/tests/util.c.o
termination_test: CMakeFiles/termination_test.dir/tests/calc_snr.c.o
termination_test: CMakeFiles/termination_test.dir/build.make
termination_test: libsamplerate.so
termination_test: CMakeFiles/termination_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andy/Embedded-Miku/libsamplerate/build_s/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable termination_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/termination_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/termination_test.dir/build: termination_test

.PHONY : CMakeFiles/termination_test.dir/build

CMakeFiles/termination_test.dir/requires: CMakeFiles/termination_test.dir/tests/termination_test.c.o.requires
CMakeFiles/termination_test.dir/requires: CMakeFiles/termination_test.dir/tests/util.c.o.requires
CMakeFiles/termination_test.dir/requires: CMakeFiles/termination_test.dir/tests/calc_snr.c.o.requires

.PHONY : CMakeFiles/termination_test.dir/requires

CMakeFiles/termination_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/termination_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/termination_test.dir/clean

CMakeFiles/termination_test.dir/depend:
	cd /home/andy/Embedded-Miku/libsamplerate/build_s && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andy/Embedded-Miku/libsamplerate /home/andy/Embedded-Miku/libsamplerate /home/andy/Embedded-Miku/libsamplerate/build_s /home/andy/Embedded-Miku/libsamplerate/build_s /home/andy/Embedded-Miku/libsamplerate/build_s/CMakeFiles/termination_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/termination_test.dir/depend

