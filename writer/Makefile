CXX=g++
SOURCES=main.cpp format.cpp drawGlyphs.cpp
CXXFLAGS=-Wall -std=gnu++11

sbdraw:
	$(CXX) -o sbdraw $(SOURCES) -I. -I/usr/include/ $(CXXFLAGS) `Magick++-config --cppflags --cxxflags --ldflags --libs`
