sbtex: main.o cmdParser.o
	g++ $(CFLAGS) -o $@ $^

dev: CFLAGS+=-g
dev: sbtex

clean:
	rm *.o sbtex

%.o: %.cpp
	g++ $(CFLAGS) -c $<

cmdParser.cpp: cmdParser.hpp defaults.hpp
