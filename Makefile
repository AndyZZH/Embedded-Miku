# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= wave_player

OBJDIR = obj
LIBDIR = libs
OUTDIR = bin

C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(wildcard $(OBJDIR)/*.o)

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc
LD = $(CROSS_TOOL)g++

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
CPPFLAGS = -Wall -g -std=c++11 -Werror

# Asound process:
# get alibsound2 lib on target:
# 	# apt-get install libasound2
# Copy target's /usr/lib/arm-linux-gnueabihf/libasound.so.2.0.0 
#      to host  ~/public/asound_lib_BBB/libasound.so
# Copy to just base library:

LFLAGS = -L$(LIBDIR)


# -pg for supporting gprof profiling.
#CFLAGS += -pg


# Makefile auto variables:
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#
# variables used in this script: $^, $<, $@


all: bt_lib $(CPP_FILES) $(C_FILES)
	$(LD) $^ -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound


# Compile all cpp files
$(C_FILES): $(OBJDIR)/%.o: %.c
	$(CC_CPP) $(CPPFLAGS) -c $< -o $@

# Compile all c files
$(CPP_FILES): $(OBJDIR)/%.o: %.cpp
	$(CC_C) $(CFLAGS) -c $< -o $@

bt_lib:
	make --directory $(LIBDIR)/btrack CROSS_TOOL=$(CROSS_TOOL)

btrack_test: btrack_lib
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

clean:
	rm -f $(OUTDIR)/$(TARGET)
