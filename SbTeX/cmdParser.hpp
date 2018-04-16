#pragma once
#include <iostream>
#include <fstream>

#include "error.hpp"

struct Info{
	std::string input;
	const char * font;
	FILE * outfile;
	const char * outfile_name;
};

void getInfo(int argc, char* argv[], Info *info);
