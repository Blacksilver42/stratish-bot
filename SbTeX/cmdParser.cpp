#include "cmdParser.hpp"
#include "defaults.hpp"
#include <string.h>
#include <stdio.h>


void getInfo(int argc, char* argv[], Info * info){
	// Parse for the -o flag to find the output file
	int i;
	info->outfile = stdout;
	info->outfile_name = "stdout";
	for(i=0;i<argc;i++){
		if(strcmp(argv[i],"-o") == 0){
			info->outfile = fopen(argv[i+1], "r");
			info->outfile_name = argv[i+1];
			break;
		}
	}
	
	// Parse for the -f <FONT> flag
	info->font = DEFAULT_FONT;
	for(i=0;i<argc;i++){
		if((strcmp(argv[i],"-f") == 0) || strcmp(argv[i],"--font") == 0){
			info->font = argv[i+1];
			break;
		}
	}
	fprintf(stderr, "Output file is '%s'; ", info->outfile_name);
	fprintf(stderr, "font is '%s'.\n", info->font);
	
	// Finally, parse the actual input.
}
