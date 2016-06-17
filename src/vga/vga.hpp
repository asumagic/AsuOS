#ifndef HVGA
#define HVGA

#include <stddef.h>
#include <stdint.h>

#include "../common/vec.hpp"

namespace vga {

// VGA terminal colors (4 bytes)
enum VGAColors
{
	COLOR_BLACK = 0,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_LIGHT_BROWN,
	COLOR_WHITE
};

class Terminal
{
public:
	Terminal();

	// Returns the VGA color with frontground and background values given
	// bg = 4 most significant bytes
	// fg = 4 least significant bytes
	constexpr static uint8_t makeColor(enum VGAColors frontground, enum VGAColors background = COLOR_BLACK)
	{
		return frontground | (background << 4);
	}

	// Returns the VGA entry with a given character and color (can be generated with makeColor).
	static uint16_t makeChar(char character, uint8_t color);

	uint16_t& operator()(vec2u position);

	void putString(const char* cstring);
	void putChar(char character);

	void scrollDown(); // Scroll down; used when reaching bottom of screen.

	void setColor(uint8_t newcolor);
	inline uint8_t getColor() const { return color; }

	void setCursorPosition(vec2u newposition);
	void updateCursor();
	inline vec2u getCursorPosition() const { return cursor; }

private:
	uint8_t color;
	const vec2u size = {80, 25};
	vec2u cursor = {0, 0};
	uint16_t* const ptr = reinterpret_cast<uint16_t*>(0xB8000); // VGA data location
};

// @TODO move to another file
size_t strlen(const char* cstring);

} // namespace vga

#endif
