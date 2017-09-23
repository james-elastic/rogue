# Makefile help from:
# - http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

CXX = g++
# to get specific SDL2 CXXFLAGS run `sdl2-config --cflags`
CXXFLAGS = -Wall -c -std=c++11 -I/usr/local/include/SDL2 -D_THREAD_SAFE
# to get specific SDL2 LDFLAGS run `sdl2-config --libs`
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image

BUILDDIR = build
SRCDIR = src
SRCEXT = cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TARGET = bin/snake

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -r $(BUILDDIR) $(TARGET)
