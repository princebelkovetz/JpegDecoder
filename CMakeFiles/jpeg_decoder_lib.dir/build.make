# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/grisha/git_testing/jpeg-decoder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/grisha/git_testing/jpeg-decoder

# Include any dependencies generated for this target.
include CMakeFiles/jpeg_decoder_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jpeg_decoder_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jpeg_decoder_lib.dir/flags.make

CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/flags.make
CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o: jpeg_decoder.cpp
CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o -MF CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o.d -o CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o -c /home/grisha/git_testing/jpeg-decoder/jpeg_decoder.cpp

CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grisha/git_testing/jpeg-decoder/jpeg_decoder.cpp > CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.i

CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grisha/git_testing/jpeg-decoder/jpeg_decoder.cpp -o CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.s

CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/flags.make
CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o: fft.cpp
CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o -MF CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o.d -o CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o -c /home/grisha/git_testing/jpeg-decoder/fft.cpp

CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grisha/git_testing/jpeg-decoder/fft.cpp > CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.i

CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grisha/git_testing/jpeg-decoder/fft.cpp -o CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.s

CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/flags.make
CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o: decoder.cpp
CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o -MF CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o.d -o CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o -c /home/grisha/git_testing/jpeg-decoder/decoder.cpp

CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grisha/git_testing/jpeg-decoder/decoder.cpp > CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.i

CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grisha/git_testing/jpeg-decoder/decoder.cpp -o CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.s

CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/flags.make
CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o: file_reader.cpp
CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o -MF CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o.d -o CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o -c /home/grisha/git_testing/jpeg-decoder/file_reader.cpp

CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grisha/git_testing/jpeg-decoder/file_reader.cpp > CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.i

CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grisha/git_testing/jpeg-decoder/file_reader.cpp -o CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.s

CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/flags.make
CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o: huffman.cpp
CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o: CMakeFiles/jpeg_decoder_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o -MF CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o.d -o CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o -c /home/grisha/git_testing/jpeg-decoder/huffman.cpp

CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grisha/git_testing/jpeg-decoder/huffman.cpp > CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.i

CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grisha/git_testing/jpeg-decoder/huffman.cpp -o CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.s

# Object files for target jpeg_decoder_lib
jpeg_decoder_lib_OBJECTS = \
"CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o" \
"CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o" \
"CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o" \
"CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o" \
"CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o"

# External object files for target jpeg_decoder_lib
jpeg_decoder_lib_EXTERNAL_OBJECTS =

libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/jpeg_decoder.cpp.o
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/fft.cpp.o
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/decoder.cpp.o
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/file_reader.cpp.o
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/huffman.cpp.o
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/build.make
libjpeg_decoder_lib.a: CMakeFiles/jpeg_decoder_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/grisha/git_testing/jpeg-decoder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libjpeg_decoder_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/jpeg_decoder_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jpeg_decoder_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jpeg_decoder_lib.dir/build: libjpeg_decoder_lib.a
.PHONY : CMakeFiles/jpeg_decoder_lib.dir/build

CMakeFiles/jpeg_decoder_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jpeg_decoder_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jpeg_decoder_lib.dir/clean

CMakeFiles/jpeg_decoder_lib.dir/depend:
	cd /home/grisha/git_testing/jpeg-decoder && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/grisha/git_testing/jpeg-decoder /home/grisha/git_testing/jpeg-decoder /home/grisha/git_testing/jpeg-decoder /home/grisha/git_testing/jpeg-decoder /home/grisha/git_testing/jpeg-decoder/CMakeFiles/jpeg_decoder_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jpeg_decoder_lib.dir/depend
