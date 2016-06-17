#ifndef HPORTIO
#define HPORTIO

#include <stdint.h>

namespace io {

inline uint8_t inByte(uint16_t port)
{
	uint8_t byte;
	asm volatile("inb %1, %0" : "=a" (byte) : "dN" (port));
	return byte;
}

inline void outByte(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" :: "dN" (port), "a" (value));
}

inline void wait()
{
	asm volatile("outb %0, $0x80" :: "a"(0));
}

}

#endif
