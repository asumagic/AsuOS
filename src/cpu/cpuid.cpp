#include "cpuid.hpp"

namespace cpuid
{

void getVendorID(char (&cpuid)[13])
{
	asm("mov $0, %eax\t\n"
		"cpuid");

	register uint32_t ebx asm("ebx"), edx asm("edx"), ecx asm("ecx");

	(*reinterpret_cast<uint32_t*>(cpuid)) = ebx;
	(*reinterpret_cast<uint32_t*>(cpuid + 4)) = edx;
	(*reinterpret_cast<uint32_t*>(cpuid + 8)) = ecx;
	cpuid[12] = 0;
}

}
