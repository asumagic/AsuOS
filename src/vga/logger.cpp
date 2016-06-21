#include "logger.hpp"

template <typename T>
const uint8_t Logger<T>::levelcolors[] = {
	vga::VGATerminal::makeColor(vga::COLOR_LIGHT_GREEN),
	vga::VGATerminal::makeColor(vga::COLOR_GREEN),
	vga::VGATerminal::makeColor(vga::COLOR_RED),
	vga::VGATerminal::makeColor(vga::COLOR_LIGHT_BROWN),
	vga::VGATerminal::makeColor(vga::COLOR_DARK_GREY)};

template <typename T>
const char* const Logger<T>::levelstrings[] = {
	"[ ** ]",
	"[ OK ]",
	"[FAIL]",
	"[WARN]",
	"[INFO]"};
