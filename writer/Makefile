CXX=g++
SOURCES=main.cpp format.cpp drawGlyphs.cpp
OBJS=main.o format.o drawGlyphs.o

CXXFLAGS=-Wall -std=gnu++11

MAGICKFLAGS:=$(shell Magick++-config --cppflags --cxxflags --ldflags --libs)

sbdraw: $(OBJS)
	$(CXX) -o sbdraw $(OBJS) -I. -I/usr/include/ $(CXXFLAGS) $(MAGICKFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) $(MAGICKFLAGS)

# extra prereqs for objects
drawGlyphs.o: presets.h drawGlyphs.hpp
format.o: format.hpp
main.o:
