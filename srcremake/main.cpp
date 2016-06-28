#include "common/includes.hpp"

extern "C"
{
	// x86-64 Kernel entry point
	void kmain()
	{
		// Initialize the FPU and related instruction sets
		fpu::fpuinitialize();


	}
}