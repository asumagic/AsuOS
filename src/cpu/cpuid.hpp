#ifndef HCPUID
#define HCPUID

#include <stdint.h>

// AsuOS checks on bootup if CPUID and advanced CPUID features are supported on bootup.
// CPUID calls shouldn't fail here.

namespace cpuid
{

// Return the CPU vendor ID (e.g. "AuthenticAMD" or "GenuineIntel")
void getVendorID(char (&cpuid)[13]);

}

#endif
