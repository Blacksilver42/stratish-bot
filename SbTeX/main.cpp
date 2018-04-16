#include <iostream>
#include <stdlib.h>
#include "cmdParser.hpp"

int main (int argc, char* argv[]){
	Info info;
	int r = getInfo(argc, argv, &info);
	if(r != 0){
		// oh, no! :(
		return r;
	}
	// phew, that worked.
}
