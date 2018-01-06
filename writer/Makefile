CXX=g++
SOURCES=main.cpp format.cpp drawGlyphs.cpp
CXXFLAGS=-Wall -std=gnu++11
MAGICKFLAGS=$(shell Magick++-config --cppflags --cxxflags --ldflags --libs)
sbdraw:
	$(CXX) -o sbdraw $(SOURCES) -I. -I/usr/include/ $(CXXFLAGS) $(MAGICKFLAGS)
