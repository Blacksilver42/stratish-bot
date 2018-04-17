#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

enum Verbosity{
	DEBUG,
	ERROR,
	QUIET,
};
struct Info{
	std::string rawInput;
	const char * font;
	char * fontpath;
	FILE * outfile;
	Verbosity verbosity;
	const char * outfile_name;
};

int getInfo(int argc, char* argv[], Info *info);
