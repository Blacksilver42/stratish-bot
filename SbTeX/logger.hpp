#pragma once
#include <iostream>

#include "cmdParser.hpp"

class Logger {
	public:
		void log(Verbosity level, std::string location, std::string what);
		Logger(Verbosity verbosity);
	private:
		Verbosity m_verbosity;
};
extern Logger logger;
