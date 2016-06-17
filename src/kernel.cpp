#include <stddef.h>
#include <stdint.h>
#include "vga/vga.hpp"
#include "vga/logger.hpp"
#include "cpu/cpuid.hpp"

extern "C"
{
	void kmain()
	{
		vga::Terminal term;
		Logger log(term);
		log.level(Logger::Info).log("AsuOS x86-64 kernel");
		log.level(Logger::Info).log("Running development build #1");

		log.level(Logger::TaskBegin).log("Initializing kernel.");

		log.level(Logger::Info).log("Running on CPU with vendor string ");
		char vendorstring[13];
		cpuid::getVendorID(vendorstring);
		term.putString(vendorstring);	

		log.level(Logger::TaskDone).log("Execution ended. Exiting.");
	}
}
