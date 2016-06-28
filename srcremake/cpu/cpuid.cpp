#include "cpuid.hpp"

namespace cpu
{
	void getVendorString(char (&string)[12])
	{
		uint32_t* registers = reinterpret_cast<uint32_t*>(&string[0]);
		asm volatile("cpuid" : "=a"(registers[0]), "=b"(registers[1]), "=c"(registers[2]), "=d"(registers[3]) : "a"(0)); // eax, ebx, ecx, edx
	}
}