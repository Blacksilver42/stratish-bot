#include "logger.hpp"
#include <stdlib.h>
#include "cmdParser.hpp"

int main (int argc, char* argv[]){
	Info info;
	int r = getInfo(argc, argv, &info);
	if(r != 0){
		logger.log(ERROR, "main", "failed to get command line info");
		return r;
	}
	// phew, that worked.
	return 0;
}
