#include "vga.hpp"
#include "../io/portio.hpp"

namespace vga {

Terminal::Terminal() : color(makeColor(COLOR_LIGHT_GREY, COLOR_BLACK))
{
	//for (size_t i = 0; i < size.x * size.y; ++i)
	//	ptr[i] = makeChar(' ', color);
}

uint16_t Terminal::makeChar(char character, uint8_t color)
{
	uint16_t char16b = character;
	uint16_t color16b = color;
	return char16b | (color16b << 8);
}

uint16_t& Terminal::operator()(vec2u position)
{
	return ptr[position.x + (position.y * size.x)];
}

void Terminal::putString(const char* cstring)
{
	int i = -1; // @TODO : avoid doing this, use size_t too
	while (cstring[++i] != 0) // != end of string character.
		putChar(cstring[i]);

	updateCursor();
}

void Terminal::putChar(char character)
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

void Terminal::scrollDown()
{
	// @TODO make a memcpy function and make it fast enough.
	
}

void Terminal::setColor(uint8_t newcolor)
{
	color = newcolor;
}

void Terminal::setCursorPosition(vec2u newposition)
{
	cursor = newposition;
}

void Terminal::updateCursor()
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
