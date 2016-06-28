#include "interrupts.hpp"

namespace pic
{

}

namespace idt
{
	Entry entries[256];
	Pointer idtptr = Pointer{sizeof(entries) - 1, entries}; // @TODO make sure this works

	void fillEntries()
	{
		for (int i = 0; i < 256; ++i) // @TODO micro-optimization - use a uint8 and rely on unsigned overflow (which is not undefined behavior) to stop the loop?
		{
			Entry& e = entries[i]; // @TODO construct the array with an initialization list (if can be done without std here)
			e.segmentselector = 0x08; // Always running off the code segment (0x08)
			e.unused = 0; // Zero out unused/reserved bits just in case
			e.unused2 = 0;

			uint64_t address = reinterpret_cast<uint64_t>(handleraddresses[i]);
			bool present = false;
			if (address)
			{
				present = true;
				e.addresslow =	   address &        0xFFFF;
				e.addressmiddle = (address << 16) & 0xFFFFFFFF;
				e.addresshigh =   (address << 24) & 0xFFFFFFFF;
			}

			e.typeattributes = (present << 7) | (0b00 << 5) | (0b0 << 4) | 0b1110; // Type & Attribute byte : 4-bit gate type (0b1110), 1 zero bit, 2 bit ring level & 1 present bit.			
		}
	}
}