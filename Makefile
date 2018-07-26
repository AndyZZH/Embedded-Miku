# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= wave_player

OBJDIR = obj
LIBDIR = libs
OUTDIR = bin

C_FILES = $(wildcard *.c)
C_OBJS = $(addprefix $(OBJDIR)/, $(C_FILES:.c=.o))
CPP_FILES = $(wildcard *.cpp)
CPP_OBJS = $(addprefix $(OBJDIR)/, $(CPP_FILES:.cpp=.o))


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

LFLAGS = -L$(LIBDIR) -lpthread -lasound -lbtrack -lsamplerate


# -pg for supporting gprof profiling.
#CFLAGS += -pg


# Makefile auto variables:
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#
# variables used in this script: $^, $<, $@


all: bt_lib setup_folders compile

compile: $(C_OBJS) $(CPP_OBJS)
	$(LD) $^ -o $(OUTDIR)/$(TARGET) $(LFLAGS)
	cp $(LIBDIR)/*.so $(OUTDIR)

# Pattern to match cpp files and use g++ to compile
$(OBJDIR)/%.o: %.cpp
	$(CC_CPP) $(CPPFLAGS) -c $< -o $@

# Pattern to match c files and use gcc to compile
$(OBJDIR)/%.o: %.c
	$(CC_C) $(CFLAGS) -c $< -o $@

setup_folders:
	mkdir -p obj
	mkdir -p bin

bt_lib:
	make --directory $(LIBDIR)/btrack CROSS_TOOL=$(CROSS_TOOL)

btrack_test: btrack_lib
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

clean:
	rm -f $(OUTDIR)/$(TARGET)
