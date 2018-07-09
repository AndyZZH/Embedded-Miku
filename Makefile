# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= wave_player

SOURCES= $(wildcard *.c)
SOURCES_CPP := $(wildcard *.cpp)
LIB_BTRACK1 := ./libs/btrack/BTrack.cpp
LIB_BTRACK2 := ./libs/btrack/OnsetDetectionFunction.cpp
LIB_BTRACK3 := ./libs/btrack/BTrack_wrapper.cpp

PUBDIR = $(HOME)/cmpt433/public/myApps
OBJDIR = ./obj
LIBDIR = ./libs/btrack
OUTDIR = $(PUBDIR)
CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
CPPFLAGS =  -c -Wall -g -Werror

# Asound process:
# get alibsound2 lib on target:
# 	# apt-get install libasound2
# Copy target's /usr/lib/arm-linux-gnueabihf/libasound.so.2.0.0 
#      to host  ~/public/asound_lib_BBB/libasound.so
# Copy to just base library:

LFLAGS = -Llibs


# -pg for supporting gprof profiling.
#CFLAGS += -pg



all: wav node
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

# Copy wave files to the shared folder
wav:
	mkdir -p $(PUBDIR)/beatbox-wav-files/
	cp beatbox-wav-files/* $(PUBDIR)/beatbox-wav-files/ 

bt_lib:
	$(CC_CPP) $(CPPFLAGS) $(LIB_BTRACK1) -o $(OBJDIR)/BTrack.o -DUSE_KISS_FFT
	$(CC_CPP) $(CPPFLAGS) $(LIB_BTRACK2) -o $(OBJDIR)/OnsetDetectionFunction.o -DUSE_KISS_FFT
	$(CC_CPP) $(CPPFLAGS) $(LIB_BTRACK3) -o $(OBJDIR)/BTrack_wrapper.o -DUSE_KISS_FFT

btrack_test: btrack_lib
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

clean:
	rm -f $(OUTDIR)/$(TARGET)
