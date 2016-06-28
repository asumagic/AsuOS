/* Port I/O functions */

#ifndef PORTIO_HPP
#define PORTIO_HPP

#include "../common/includes.hpp"

namespace io
{
	// Gets unsigned integers for 8, 16, 32 and 64 bit values from a given port
	template<typename inT> inT in(uint16_t port); // Primary template function
	template<> uint8_t in(uint16_t port); 
	template<> uint16_t in(uint16_t port);
	template<> uint32_t in(uint16_t port);
	//template<> uint64_t in(uint16_t port);

	// Outputs unsigned integers for 8, 16, 32 and 64 bit values to a given port
	template<typename outT> void out(uint16_t port, outT value);
	template<> void out(uint16_t port, uint8_t value);
	template<> void out(uint16_t port, uint16_t value);
	template<> void out(uint16_t port, uint32_t value);
	//template<> void out(uint16_t port, uint64_t value);

	// Waits for an i/o operation to complete
	void wait();
}

#include "portio.tpp"

#endif