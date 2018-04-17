#include <stdio.h>

#include "logger.hpp"
#include "cmdParser.hpp"

Logger::Logger(Verbosity verbosity){
	m_verbosity = verbosity;
}

void Logger::log(Verbosity level, std::string location, std::string what){
	if (level >= m_verbosity){
		if (level == ERROR)
			fprintf(stderr, "[ERROR] @%s: %s\n", location.c_str(), what.c_str());
		else
			fprintf(stdout, "[DEBUG] @%s: %s\n", location.c_str(), what.c_str());
	}
}
