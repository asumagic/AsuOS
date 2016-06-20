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
		log(Logger::Info) << "AsuOS x86-64 kernel";
		log(Logger::Info) << "Running development build #1";

		log(Logger::TaskBegin) << "Initializing kernel.";

		char vendorstring[13];
		cpuid::getVendorString(vendorstring);
		log(Logger::Info) << "CPU vendor '" << vendorstring << "'";

		log(Logger::TaskBegin) << "Preparing interruptions...";
		interrupts::initialize();
		//log.updateStatus(Logger::TaskDone);

		log(Logger::TaskDone) << "Execution ended. Exiting.";
	}
}
