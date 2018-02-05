<<<<<<< HEAD
.PHONY: clean
=======
.PHONY: clean cleanobj cleanbin
>>>>>>> razor

CXX=g++
SOURCES=main.cpp format.cpp drawGlyphs.cpp
OBJS=main.o format.o drawGlyphs.o

CXXFLAGS=-Wall -Wextra -Wpedantic -std=gnu++11

MAGICKFLAGS:=$(shell Magick++-config --cppflags --cxxflags --ldflags --libs)



sbdraw: $(OBJS)
	$(CXX) -o sbdraw $(OBJS) $(CXXFLAGS) $(MAGICKFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) $(MAGICKFLAGS)

<<<<<<< HEAD
clean:
	rm *.o sbdraw
=======
# extra prereqs for objects
drawGlyphs.o: presets.h drawGlyphs.hpp
format.o: format.hpp
main.o:


clean: cleanobj cleanbin

cleanobj:
	rm -rf *.o

cleanbin:
	rm -rf sbdraw
>>>>>>> razor
