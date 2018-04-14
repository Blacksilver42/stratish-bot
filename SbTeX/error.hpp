#include <iostream>

struct Error{
	std::string function;
	std::string reason;
};

void printError(Error error);
