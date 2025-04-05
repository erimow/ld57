#OBJS specifies which files to compile as part of the project
OBJS = main.c 

SOURCES :=   $(wildcard Scripts/*.c) $(wildcard Engine/*.c) #$(wildcard ./*.c)

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -Wall -Wextra -g -ggdb3 -O0

#INCLUDES
INCLUDES = -I./Sounds -I./Art -I./Engine -I./Fonts -I./

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL3 -lSDL3_image -lm -lSDL3_ttf #-lSDL2_mixer -lSDL2_ttf -lm

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = play

#This is the target that compiles our executable
all : $(SOURCES)
	$(CC) $(OBJS) $(SOURCES) $(COMPILER_FLAGS) $(INCLUDES) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./play
