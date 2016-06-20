#ifndef HLOGGER
#define HLOGGER

#include <stddef.h>
#include <stdint.h>

#include "vga.hpp"

class Logger
{
public:
	enum Levels
	{
		TaskBegin = 0,
		TaskDone,
		TaskFailure,
		TaskWarning,
		Info
	};

	static const uint8_t levelcolors[5];
	static const char* const levelstrings[5];

	Logger(vga::VGATerminal& term);

	Logger& operator()(enum Levels loglevel);
	Logger& operator<<(const char* cstring);

private:
	vga::VGATerminal& term;

	Levels currentLevel;

	bool skipFirst = true;
};

#endif
