# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= miku

OBJDIR = obj
LIBDIR = libs
OUTDIR = $(HOME)/cmpt433/public/myApps

C_FILES = $(wildcard *.c)
# Filter out ledTest.c since it is a testing module
C_FILES := $(filter-out ledTest.c, $(C_FILES))

C_OBJS = $(addprefix $(OBJDIR)/, $(C_FILES:.c=.o))
CPP_FILES = $(wildcard *.cpp)
CPP_OBJS = $(addprefix $(OBJDIR)/, $(CPP_FILES:.cpp=.o))


CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc
LD = $(CROSS_TOOL)g++

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
CPPFLAGS = -Wall -g -std=c++11 -Werror

# If CROSS_TOOL is not defined, we are compiling on host and use -L$(LIBDIR)/x86-linux as linker folder
# otherwise, we will use -L$(LIBDIR)/arm-linux as linker folder
ifeq ($(CROSS_TOOL),)
	LFLAGS := -L$(LIBDIR)/x86-linux
else ifeq ($(CROSS_TOOL),arm-linux-gnueabihf-)
	LFLAGS := -L$(LIBDIR)/arm-linux
endif

# LFLAGS = -lpthread -lasound -lbtrack -lsamplerate
LFLAGS += -lpthread -lasound -laubio -Wl,-unresolved-symbols=ignore-in-shared-libs


# -pg for supporting gprof profiling.
#CFLAGS += -pg


# Makefile auto variables:
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#
# variables used in this script: $^, $<, $@


all: setup_folders compile

compile: $(C_OBJS) $(CPP_OBJS)
	$(LD) $^ -o $(OUTDIR)/$(TARGET) $(LFLAGS)

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
	rm -rf $(OBJDIR)
	rm -f $(OUTDIR)/$(TARGET)
