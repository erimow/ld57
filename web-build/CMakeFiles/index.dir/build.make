# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = /home/erik/Projects/ld57

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erik/Projects/ld57/web-build

# Include any dependencies generated for this target.
include CMakeFiles/index.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/index.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/index.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/index.dir/flags.make

CMakeFiles/index.dir/codegen:
.PHONY : CMakeFiles/index.dir/codegen

CMakeFiles/index.dir/Engine/BackgroundEntity.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/BackgroundEntity.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/BackgroundEntity.c.o: /home/erik/Projects/ld57/Engine/BackgroundEntity.c
CMakeFiles/index.dir/Engine/BackgroundEntity.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/index.dir/Engine/BackgroundEntity.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/BackgroundEntity.c.o -MF CMakeFiles/index.dir/Engine/BackgroundEntity.c.o.d -o CMakeFiles/index.dir/Engine/BackgroundEntity.c.o -c /home/erik/Projects/ld57/Engine/BackgroundEntity.c

CMakeFiles/index.dir/Engine/BackgroundEntity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/BackgroundEntity.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/BackgroundEntity.c > CMakeFiles/index.dir/Engine/BackgroundEntity.c.i

CMakeFiles/index.dir/Engine/BackgroundEntity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/BackgroundEntity.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/BackgroundEntity.c -o CMakeFiles/index.dir/Engine/BackgroundEntity.c.s

CMakeFiles/index.dir/Engine/Button.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Button.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Button.c.o: /home/erik/Projects/ld57/Engine/Button.c
CMakeFiles/index.dir/Engine/Button.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/index.dir/Engine/Button.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Button.c.o -MF CMakeFiles/index.dir/Engine/Button.c.o.d -o CMakeFiles/index.dir/Engine/Button.c.o -c /home/erik/Projects/ld57/Engine/Button.c

CMakeFiles/index.dir/Engine/Button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Button.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Button.c > CMakeFiles/index.dir/Engine/Button.c.i

CMakeFiles/index.dir/Engine/Button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Button.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Button.c -o CMakeFiles/index.dir/Engine/Button.c.s

CMakeFiles/index.dir/Engine/Camera.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Camera.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Camera.c.o: /home/erik/Projects/ld57/Engine/Camera.c
CMakeFiles/index.dir/Engine/Camera.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/index.dir/Engine/Camera.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Camera.c.o -MF CMakeFiles/index.dir/Engine/Camera.c.o.d -o CMakeFiles/index.dir/Engine/Camera.c.o -c /home/erik/Projects/ld57/Engine/Camera.c

CMakeFiles/index.dir/Engine/Camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Camera.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Camera.c > CMakeFiles/index.dir/Engine/Camera.c.i

CMakeFiles/index.dir/Engine/Camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Camera.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Camera.c -o CMakeFiles/index.dir/Engine/Camera.c.s

CMakeFiles/index.dir/Engine/Entity.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Entity.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Entity.c.o: /home/erik/Projects/ld57/Engine/Entity.c
CMakeFiles/index.dir/Engine/Entity.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/index.dir/Engine/Entity.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Entity.c.o -MF CMakeFiles/index.dir/Engine/Entity.c.o.d -o CMakeFiles/index.dir/Engine/Entity.c.o -c /home/erik/Projects/ld57/Engine/Entity.c

CMakeFiles/index.dir/Engine/Entity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Entity.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Entity.c > CMakeFiles/index.dir/Engine/Entity.c.i

CMakeFiles/index.dir/Engine/Entity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Entity.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Entity.c -o CMakeFiles/index.dir/Engine/Entity.c.s

CMakeFiles/index.dir/Engine/Texture.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Texture.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Texture.c.o: /home/erik/Projects/ld57/Engine/Texture.c
CMakeFiles/index.dir/Engine/Texture.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/index.dir/Engine/Texture.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Texture.c.o -MF CMakeFiles/index.dir/Engine/Texture.c.o.d -o CMakeFiles/index.dir/Engine/Texture.c.o -c /home/erik/Projects/ld57/Engine/Texture.c

CMakeFiles/index.dir/Engine/Texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Texture.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Texture.c > CMakeFiles/index.dir/Engine/Texture.c.i

CMakeFiles/index.dir/Engine/Texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Texture.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Texture.c -o CMakeFiles/index.dir/Engine/Texture.c.s

CMakeFiles/index.dir/Engine/Tilemap.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Tilemap.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Tilemap.c.o: /home/erik/Projects/ld57/Engine/Tilemap.c
CMakeFiles/index.dir/Engine/Tilemap.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/index.dir/Engine/Tilemap.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Tilemap.c.o -MF CMakeFiles/index.dir/Engine/Tilemap.c.o.d -o CMakeFiles/index.dir/Engine/Tilemap.c.o -c /home/erik/Projects/ld57/Engine/Tilemap.c

CMakeFiles/index.dir/Engine/Tilemap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Tilemap.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Tilemap.c > CMakeFiles/index.dir/Engine/Tilemap.c.i

CMakeFiles/index.dir/Engine/Tilemap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Tilemap.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Tilemap.c -o CMakeFiles/index.dir/Engine/Tilemap.c.s

CMakeFiles/index.dir/Engine/Timer.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/Timer.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/Timer.c.o: /home/erik/Projects/ld57/Engine/Timer.c
CMakeFiles/index.dir/Engine/Timer.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/index.dir/Engine/Timer.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/Timer.c.o -MF CMakeFiles/index.dir/Engine/Timer.c.o.d -o CMakeFiles/index.dir/Engine/Timer.c.o -c /home/erik/Projects/ld57/Engine/Timer.c

CMakeFiles/index.dir/Engine/Timer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/Timer.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/Timer.c > CMakeFiles/index.dir/Engine/Timer.c.i

CMakeFiles/index.dir/Engine/Timer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/Timer.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/Timer.c -o CMakeFiles/index.dir/Engine/Timer.c.s

CMakeFiles/index.dir/Engine/efuncs.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/efuncs.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/efuncs.c.o: /home/erik/Projects/ld57/Engine/efuncs.c
CMakeFiles/index.dir/Engine/efuncs.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/index.dir/Engine/efuncs.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/efuncs.c.o -MF CMakeFiles/index.dir/Engine/efuncs.c.o.d -o CMakeFiles/index.dir/Engine/efuncs.c.o -c /home/erik/Projects/ld57/Engine/efuncs.c

CMakeFiles/index.dir/Engine/efuncs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/efuncs.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/efuncs.c > CMakeFiles/index.dir/Engine/efuncs.c.i

CMakeFiles/index.dir/Engine/efuncs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/efuncs.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/efuncs.c -o CMakeFiles/index.dir/Engine/efuncs.c.s

CMakeFiles/index.dir/Engine/scenemanager.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Engine/scenemanager.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Engine/scenemanager.c.o: /home/erik/Projects/ld57/Engine/scenemanager.c
CMakeFiles/index.dir/Engine/scenemanager.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/index.dir/Engine/scenemanager.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Engine/scenemanager.c.o -MF CMakeFiles/index.dir/Engine/scenemanager.c.o.d -o CMakeFiles/index.dir/Engine/scenemanager.c.o -c /home/erik/Projects/ld57/Engine/scenemanager.c

CMakeFiles/index.dir/Engine/scenemanager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Engine/scenemanager.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Engine/scenemanager.c > CMakeFiles/index.dir/Engine/scenemanager.c.i

CMakeFiles/index.dir/Engine/scenemanager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Engine/scenemanager.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Engine/scenemanager.c -o CMakeFiles/index.dir/Engine/scenemanager.c.s

CMakeFiles/index.dir/Scripts/game.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Scripts/game.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Scripts/game.c.o: /home/erik/Projects/ld57/Scripts/game.c
CMakeFiles/index.dir/Scripts/game.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/index.dir/Scripts/game.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Scripts/game.c.o -MF CMakeFiles/index.dir/Scripts/game.c.o.d -o CMakeFiles/index.dir/Scripts/game.c.o -c /home/erik/Projects/ld57/Scripts/game.c

CMakeFiles/index.dir/Scripts/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Scripts/game.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Scripts/game.c > CMakeFiles/index.dir/Scripts/game.c.i

CMakeFiles/index.dir/Scripts/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Scripts/game.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Scripts/game.c -o CMakeFiles/index.dir/Scripts/game.c.s

CMakeFiles/index.dir/Scripts/maingamescene.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Scripts/maingamescene.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Scripts/maingamescene.c.o: /home/erik/Projects/ld57/Scripts/maingamescene.c
CMakeFiles/index.dir/Scripts/maingamescene.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/index.dir/Scripts/maingamescene.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Scripts/maingamescene.c.o -MF CMakeFiles/index.dir/Scripts/maingamescene.c.o.d -o CMakeFiles/index.dir/Scripts/maingamescene.c.o -c /home/erik/Projects/ld57/Scripts/maingamescene.c

CMakeFiles/index.dir/Scripts/maingamescene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Scripts/maingamescene.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Scripts/maingamescene.c > CMakeFiles/index.dir/Scripts/maingamescene.c.i

CMakeFiles/index.dir/Scripts/maingamescene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Scripts/maingamescene.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Scripts/maingamescene.c -o CMakeFiles/index.dir/Scripts/maingamescene.c.s

CMakeFiles/index.dir/Scripts/mainmenu.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/Scripts/mainmenu.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/Scripts/mainmenu.c.o: /home/erik/Projects/ld57/Scripts/mainmenu.c
CMakeFiles/index.dir/Scripts/mainmenu.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/index.dir/Scripts/mainmenu.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/Scripts/mainmenu.c.o -MF CMakeFiles/index.dir/Scripts/mainmenu.c.o.d -o CMakeFiles/index.dir/Scripts/mainmenu.c.o -c /home/erik/Projects/ld57/Scripts/mainmenu.c

CMakeFiles/index.dir/Scripts/mainmenu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/Scripts/mainmenu.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/Scripts/mainmenu.c > CMakeFiles/index.dir/Scripts/mainmenu.c.i

CMakeFiles/index.dir/Scripts/mainmenu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/Scripts/mainmenu.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/Scripts/mainmenu.c -o CMakeFiles/index.dir/Scripts/mainmenu.c.s

CMakeFiles/index.dir/main.c.o: CMakeFiles/index.dir/flags.make
CMakeFiles/index.dir/main.c.o: CMakeFiles/index.dir/includes_C.rsp
CMakeFiles/index.dir/main.c.o: /home/erik/Projects/ld57/main.c
CMakeFiles/index.dir/main.c.o: CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/index.dir/main.c.o"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/index.dir/main.c.o -MF CMakeFiles/index.dir/main.c.o.d -o CMakeFiles/index.dir/main.c.o -c /home/erik/Projects/ld57/main.c

CMakeFiles/index.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/index.dir/main.c.i"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/erik/Projects/ld57/main.c > CMakeFiles/index.dir/main.c.i

CMakeFiles/index.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/index.dir/main.c.s"
	emcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/erik/Projects/ld57/main.c -o CMakeFiles/index.dir/main.c.s

# Object files for target index
index_OBJECTS = \
"CMakeFiles/index.dir/Engine/BackgroundEntity.c.o" \
"CMakeFiles/index.dir/Engine/Button.c.o" \
"CMakeFiles/index.dir/Engine/Camera.c.o" \
"CMakeFiles/index.dir/Engine/Entity.c.o" \
"CMakeFiles/index.dir/Engine/Texture.c.o" \
"CMakeFiles/index.dir/Engine/Tilemap.c.o" \
"CMakeFiles/index.dir/Engine/Timer.c.o" \
"CMakeFiles/index.dir/Engine/efuncs.c.o" \
"CMakeFiles/index.dir/Engine/scenemanager.c.o" \
"CMakeFiles/index.dir/Scripts/game.c.o" \
"CMakeFiles/index.dir/Scripts/maingamescene.c.o" \
"CMakeFiles/index.dir/Scripts/mainmenu.c.o" \
"CMakeFiles/index.dir/main.c.o"

# External object files for target index
index_EXTERNAL_OBJECTS =

index.html: CMakeFiles/index.dir/Engine/BackgroundEntity.c.o
index.html: CMakeFiles/index.dir/Engine/Button.c.o
index.html: CMakeFiles/index.dir/Engine/Camera.c.o
index.html: CMakeFiles/index.dir/Engine/Entity.c.o
index.html: CMakeFiles/index.dir/Engine/Texture.c.o
index.html: CMakeFiles/index.dir/Engine/Tilemap.c.o
index.html: CMakeFiles/index.dir/Engine/Timer.c.o
index.html: CMakeFiles/index.dir/Engine/efuncs.c.o
index.html: CMakeFiles/index.dir/Engine/scenemanager.c.o
index.html: CMakeFiles/index.dir/Scripts/game.c.o
index.html: CMakeFiles/index.dir/Scripts/maingamescene.c.o
index.html: CMakeFiles/index.dir/Scripts/mainmenu.c.o
index.html: CMakeFiles/index.dir/main.c.o
index.html: CMakeFiles/index.dir/build.make
index.html: CMakeFiles/index.dir/linkLibs.rsp
index.html: CMakeFiles/index.dir/objects1.rsp
index.html: CMakeFiles/index.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/erik/Projects/ld57/web-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C executable index.html"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/index.dir/build: index.html
.PHONY : CMakeFiles/index.dir/build

CMakeFiles/index.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean.cmake
.PHONY : CMakeFiles/index.dir/clean

CMakeFiles/index.dir/depend:
	cd /home/erik/Projects/ld57/web-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erik/Projects/ld57 /home/erik/Projects/ld57 /home/erik/Projects/ld57/web-build /home/erik/Projects/ld57/web-build /home/erik/Projects/ld57/web-build/CMakeFiles/index.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/index.dir/depend

