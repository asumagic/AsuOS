#include "portio.hpp"

namespace io
{
	// Port input template implementations
	template<> uint8_t in(uint16_t port)
	{
		uint8_t ret;
		asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port)); // inbyte
		return ret;
	}

	template<> uint16_t in(uint16_t port)
	{
		uint16_t ret;
		asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port)); // inword
		return ret;
	}

	template<> uint32_t in(uint16_t port)
	{
		uint32_t ret;
		asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port)); // inlong
		return ret;
	}

	/*template<> uint64_t in(uint16_t port)
	{
		uint32_t ret;
		asm volatile("inq %1, %0" : "=a"(ret) : "Nd"(port)); // inquad
		return ret;
	}*/

	// Port output template implementations
	template<> void out(uint16_t port, uint8_t value)
	{
		asm volatile("outb %0, %1" :: "a"(value), "Nd"(port)); // inbyte
	}

	template<> void out(uint16_t port, uint16_t value)
	{
		asm volatile("outw %0, %1" :: "a"(value), "Nd"(port)); // inword
	}

	template<> void out(uint16_t port, uint32_t value)
	{
		asm volatile("outl %0, %1" :: "a"(value), "Nd"(port)); // inlong
	}

	/*template<> void out(uint16_t port, uint64_t value)
	{
		asm volatile("outq %0, %1" :: "a"(value), "Nd"(port)); // inquad
	}*/
}