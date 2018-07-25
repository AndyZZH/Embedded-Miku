
SOURCES = BTrack.cpp OnsetDetectionFunction.cpp BTrack_wrapper.cpp
TARGET = btrack.so

OUTDIR = ../
LIBSDIR = ../

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++

CPPFLAGS = -Wall -g -Werror -fPIC -DUSE_KISS_FFT
LFLAGS = -L$(LIBSDIR) -shared

# Generating btrack.so
# Adding -fPIC and -shared flag to generate the dynamic .so object as described in 
# https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line

all:
	$(CC_CPP) $(CPPFLAGS) $(LFLAGS) -o $(OUTDIR)$(TARGET) $(SOURCES)
