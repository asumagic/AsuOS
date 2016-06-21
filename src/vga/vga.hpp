#ifndef HVGA
#define HVGA

#include <stddef.h>
#include <stdint.h>

#include "terminal.hpp"
#include "../common/vec.hpp"
#include "../module/module.hpp"

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

// Generic text-mode VGA terminal
class VGATerminal : public TerminalColorDriver<uint16_t, uint8_t, uint8_t>
{
public:
	VGATerminal();
	
	Module::loadResult moduleLoad() override;

	// Returns the VGA color with frontground and background values given
	// bg = 4 most significant bytes
	// fg = 4 least significant bytes
	constexpr uint8_t makeColor(enum VGAColors frontground, enum VGAColors background = COLOR_BLACK) override
	{
		return frontground | (background << 4);
	}

	// Returns the VGA entry with a given character and color (can be generated with makeColor).
	static uint16_t makeChar(char character, uint8_t color);

	uint16_t& operator()(vec2u position);

	void putChar(char character) override;

	void scrollDown(); // Scroll down; used when reaching bottom of screen.

	void setColor(uint8_t newcolor) override;
	inline uint8_t getColor() const override { return color; }

	void setCursorPosition(vec2u newposition) override;
	void updateCursor() override;
	inline vec2u getCursorPosition() const override { return cursor; }

	inline uint16_t* getFramebuffer() const override { return ptr; }

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
