#include "logger.hpp"

Logger::Logger(vga::Terminal& term) : term(term) {}

Logger& Logger::level(enum Levels loglevel)
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

void Logger::log(const char* cstring)
{
	term.putString(cstring);
}

const uint8_t Logger::levelcolors[] = {
	vga::Terminal::makeColor(vga::COLOR_LIGHT_GREEN),
	vga::Terminal::makeColor(vga::COLOR_GREEN),
	vga::Terminal::makeColor(vga::COLOR_RED),
	vga::Terminal::makeColor(vga::COLOR_LIGHT_BROWN),
	vga::Terminal::makeColor(vga::COLOR_DARK_GREY)};

const char* const Logger::levelstrings[] = {
	"[ ** ]",
	"[ OK ]",
	"[FAIL]",
	"[WARN]",
	"[INFO]"};
