CXX = g++
# to get specific SDL2 CXXFLAGS run `sdl2-config --cflags`
CXXFLAGS = -Wall -c -std=c++11 -I/usr/local/include/SDL2 -D_THREAD_SAFE
# to get specific SDL2 LDFLAGS run `sdl2-config --libs`
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image #-framework SDL2
EXE = snake

all: $(EXE)

$(EXE): error.o util.o main.o
	$(CXX) $(LDFLAGS) $^ -o $@

error.o: error.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

util.o: util.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm *.o && rm $(EXE)

forceclean:
	rm -f *.o && rm -f $(EXE) && rm -f *~
