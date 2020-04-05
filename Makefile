# Makefile help from:
# - http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

CXX = g++
INCLUDE_PATHS  = -I/usr/local/include/SDL2
LIBRARY_PATHS  = -L/usr/local/lib -lSDL2 -lSDL2_image

COMPILER_FLAGS = -Wall -c -std=c++11 -D_THREAD_SAFE
LINKER_FLAGS   = -framework OpenGL
# to get specific SDL2 CXXFLAGS run `sdl2-config --cflags`
CXXFLAGS = -Wall -c -std=c++11 -I/usr/local/include/SDL2 -D_THREAD_SAFE -framework OpenGL
# to get specific SDL2 LDFLAGS run `sdl2-config --libs`


BUILDDIR = build
SRCDIR = src
SRCEXT = cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TARGET = bin/rogue

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LINKER_FLAGS) $(LIBRARY_PATHS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $< -o $@

clean:
	rm -r $(BUILDDIR) $(TARGET)
