#ifndef FPU_HPP
#define FPU_HPP

namespace fpu
{
	extern "C"
	{
		extern void fpuinitialize(); // Initialize the x87 float processing unit and the SSE instruction set
	}
}

#endif