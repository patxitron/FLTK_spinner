PROJECT_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
COMPILER_PREFIX :=
STRIP = $(COMPILER_PREFIX)strip
STRIPFLAGS = --strip-all
CXXFLAGS = -std=c++14 -pedantic -fmessage-length=0 `fltk-config --cxxflags`
OPTFLAGS = -O2
DBGFLAGS = -O0 -g -DDEBUG
LDFLAGS =
CXX := $(COMPILER_PREFIX)g++
CC := $(COMPILER_PREFIX)gcc

OBJS := main.o spinner.o uintspinner.o
LIBS = -lm `fltk-config --ldflags`

TARGET = spinner_test

all: release

debug: CXXFLAGS := $(DBGFLAGS) $(CXXFLAGS)
debug: $(TARGET)

release: CXXFLAGS := $(OPTFLAGS) $(CXXFLAGS)
release: $(TARGET)
	$(STRIP) $(STRIPFLAGS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
