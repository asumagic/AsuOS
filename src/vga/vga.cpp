#include "vga.hpp"
#include "../io/portio.hpp"

namespace vga {

VGATerminal::VGATerminal() : color(makeColor(COLOR_LIGHT_GREY, COLOR_BLACK)) {}

Module::loadResult VGATerminal::moduleLoad()
{
	// @TODO check if another driver uses the terminal
	return LDSUCCESS;
}

uint16_t VGATerminal::makeChar(char character, uint8_t color)
{
	uint16_t char16b = character;
	uint16_t color16b = color;
	return char16b | (color16b << 8);
}

uint16_t& VGATerminal::operator()(vec2u position)
{
	return ptr[position.x + (position.y * size.x)];
}

void VGATerminal::putChar(char character)
{
	switch (character)
	{
	case '\n':
		cursor = vec2u{0, cursor.y + 1};
		break;
	case '\r':
		cursor.x = 0;
		break;
	// @TODO : \a \t \v
	default:
		ptr[cursor.x + (cursor.y * size.x)] = makeChar(character, color);
		if (++cursor.x == size.x)
			cursor = vec2u{0, cursor.y + 1};

		if (cursor.y == size.y)
			scrollDown();
	}
}

void VGATerminal::scrollDown()
{
	// @TODO make a memcpy function and make it fast enough.
	
}

void VGATerminal::setColor(uint8_t newcolor)
{
	color = newcolor;
}

void VGATerminal::setCursorPosition(vec2u newposition)
{
	cursor = newposition;
}

void VGATerminal::updateCursor()
{
	unsigned int index = (cursor.x + (cursor.y * size.x));

	io::outByte(0x3D4, 14);
	io::outByte(0x3D5, index >> 8);

	io::outByte(0x3D4, 15);
	io::outByte(0x3D5, index);
}

size_t strlen(const char* cstring)
{
	size_t size = 0;
	while (cstring[size] != 0) ++size;
	return size;
}

} // namespace vga
