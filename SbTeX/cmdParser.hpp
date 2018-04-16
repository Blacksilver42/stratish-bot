#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>


struct Info{
	std::string input;
	const char * font;
	char * fontpath;
	FILE * outfile;
	const char * outfile_name;
};

int getInfo(int argc, char* argv[], Info *info);
