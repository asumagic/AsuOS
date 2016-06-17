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

	Logger(vga::Terminal& term);

	Logger& level(enum Levels loglevel);
	void log(const char* cstring);

private:
	vga::Terminal& term;

	Levels currentLevel;

	bool skipFirst = true;
};

#endif
