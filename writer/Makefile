.PHONY: clean

CXX=g++
SOURCES=main.cpp format.cpp drawGlyphs.cpp
OBJS=main.o format.o drawGlyphs.o

CXXFLAGS=-Wall -std=gnu++11

MAGICKFLAGS=$(shell Magick++-config --cppflags --cxxflags --ldflags --libs)

sbdraw: $(OBJS)
	$(CXX) -o sbdraw $(OBJS) $(CXXFLAGS) $(MAGICKFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) $(MAGICKFLAGS)

clean:
	rm *.o sbdraw
