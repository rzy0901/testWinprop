# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Download\Clion\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Download\Clion\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Codes\testWinprop_v2\testWinprop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\indoor_trajectory.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\indoor_trajectory.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\indoor_trajectory.dir\flags.make

CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.obj: CMakeFiles\indoor_trajectory.dir\flags.make
CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.obj: ..\indoor_trajectory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/indoor_trajectory.dir/indoor_trajectory.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.obj /FdCMakeFiles\indoor_trajectory.dir\ /FS -c D:\Codes\testWinprop_v2\testWinprop\indoor_trajectory.cpp
<<

CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/indoor_trajectory.dir/indoor_trajectory.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx64\x64\cl.exe > CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Codes\testWinprop_v2\testWinprop\indoor_trajectory.cpp
<<

CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/indoor_trajectory.dir/indoor_trajectory.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.s /c D:\Codes\testWinprop_v2\testWinprop\indoor_trajectory.cpp
<<

# Object files for target indoor_trajectory
indoor_trajectory_OBJECTS = \
"CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.obj"

# External object files for target indoor_trajectory
indoor_trajectory_EXTERNAL_OBJECTS =

indoor_trajectory.exe: CMakeFiles\indoor_trajectory.dir\indoor_trajectory.cpp.obj
indoor_trajectory.exe: CMakeFiles\indoor_trajectory.dir\build.make
indoor_trajectory.exe: D:\Download\Altair_2021\feko\api\winprop\export\winprop\64\Engine.lib
indoor_trajectory.exe: CMakeFiles\indoor_trajectory.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable indoor_trajectory.exe"
	"D:\Download\Clion\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\indoor_trajectory.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\indoor_trajectory.dir\objects1.rsp @<<
 /out:indoor_trajectory.exe /implib:indoor_trajectory.lib /pdb:D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug\indoor_trajectory.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console  D:\Download\Altair_2021\feko\api\winprop\export\winprop\64\Engine.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\indoor_trajectory.dir\build: indoor_trajectory.exe

.PHONY : CMakeFiles\indoor_trajectory.dir\build

CMakeFiles\indoor_trajectory.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\indoor_trajectory.dir\cmake_clean.cmake
.PHONY : CMakeFiles\indoor_trajectory.dir\clean

CMakeFiles\indoor_trajectory.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Codes\testWinprop_v2\testWinprop D:\Codes\testWinprop_v2\testWinprop D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug D:\Codes\testWinprop_v2\testWinprop\cmake-build-debug\CMakeFiles\indoor_trajectory.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\indoor_trajectory.dir\depend
