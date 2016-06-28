/* Handle pure virtual function calls for C++ virtuals */

#ifndef PUREVIRTUAL_HPP
#define PUREVIRTUAL_HPP

extern "C"
{
	void __cxa_pure_virtual(); // Handle pure virtual function calls
}

#endif