#ifndef HLOGGER
#define HLOGGER

#include <stddef.h>
#include <stdint.h>

#include "vga.hpp"

template<typename T>
class Logger
{
public:
	Logger(T& driver) : term(driver) {}

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

	Logger<T>& operator()(enum Levels loglevel)
	{
		if (term.getCursorPosition().y == 0) // @TODO : Avoid needing skipFirst?
		skipFirst = !skipFirst;
	
		if (skipFirst)
			term.putChar('\n');

		currentLevel = loglevel;
		size_t n = static_cast<size_t>(loglevel);
		
		uint8_t prevcolor = term.getColor();
		term.setColor(levelcolors[n]);
		term.putString(levelstrings[n]);
		
		term.setColor(prevcolor);
		term.putChar(' ');

		return *this;
	}
	
	Logger<T>& operator<<(const char* cstring)
	{
		term.putString(cstring);
		return *this;
	}

private:
	T& term;

	Levels currentLevel;

	bool skipFirst = true;
};

#endif
