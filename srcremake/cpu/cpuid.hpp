/* CPUID related functions
   Used to get various information from the CPU (vendor string, etc.)
   The bootloader checks if CPUID functions (and if advanced ones are), so most functions here *shouldn't* fail. */

#ifndef CPUID_HPP
#define CPUID_HPP

#include <stdint.h>

namespace cpu
{
	// Return the 12-bit string vendor string (e.g. "GenuineIntel", "AuthenticAMD")
	void getVendorString(char (&string)[12]);
}

#endif