#include <stddef.h>
#include <stdint.h>
#include "vga/vga.hpp"
#include "vga/logger.hpp"
#include "cpu/cpuid.hpp"
#include "cpu/interrupts.hpp"

extern "C"
{
	void kmain()
	{
		vga::Terminal term;
		Logger log(term);
		log.level(Logger::Info).log("AsuOS x86-64 kernel");
		log.level(Logger::Info).log("Running development build #1");

		log.level(Logger::TaskBegin).log("Initializing kernel.");

		log.level(Logger::Info).log("CPU vendor '");
		char vendorstring[13];
		cpuid::getVendorID(vendorstring);
		term.putString(vendorstring);
		term.putChar('\'');

		log.level(Logger::TaskBegin).log("Initializing PIC...");
		interrupts::initialize();

		log.level(Logger::TaskDone).log("Falling in infinite loop.");	

		for(;;);

		log.level(Logger::TaskDone).log("Execution ended. Exiting.");
	}
}
