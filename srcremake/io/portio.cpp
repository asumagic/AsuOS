#include "portio.hpp"

namespace io
{
	void wait()
	{
		asm volatile("outb %%al, $0x80" :: "a"(0));
	}
}