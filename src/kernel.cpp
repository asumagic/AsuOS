#include <stddef.h>
#include <stdint.h>
#include "vga/vga.hpp"
#include "vga/logger.hpp"
#include "cpu/cpuid.hpp"
#include "cpu/interrupts.hpp"
#include "common/kernel.hpp"

extern "C"
{
	void kmain()
	{
		Kernel kinst;

		//// TEMPORARY HACK @TODO dynamic allocation ////

		vga::VGATerminal term;
		kinst.modules[0] = &term;

		//// END OF TEMPORARY HACK ////

		kinst.initializeModules();

		Logger<vga::VGATerminal> log(term);
		log(log.Info) << "AsuOS x86-64 kernel";
		log(log.Info) << "Running development build #1";

		log(log.TaskBegin) << "Initializing kernel.";

		char vendorstring[13];
		cpuid::getVendorString(vendorstring);
		log(log.Info) << "CPU vendor '" << vendorstring << "'";

		log(log.TaskBegin) << "Preparing interruptions...";
		interrupts::initialize();
		//log.updateStatus(Logger::TaskDone);

		log(log.TaskDone) << "Execution ended. Exiting.";
	}
}
