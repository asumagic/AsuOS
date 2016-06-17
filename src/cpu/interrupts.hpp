#ifndef HINTERRUPTS
#define HINTERRUPTS

#include <stdint.h>

namespace interrupts
{
	struct PIC
	{
		uint8_t addr, cmd, data;
		enum commands
		{
			EOI = 0x20
		};
	};
}

#endif
