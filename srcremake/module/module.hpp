/* Defines the main module class relying on static polymorphism with CRTP */

#ifndef MODULE_HPP
#define MODULE_HPP

template<class implc>
class Module
{
public:
	enum abortReason
	{
		KERNEL_SHUTDOWN = 0,	// Normal kernel shutdown
		MODULE_DEACTIVATED,		// User or kernel module deactivation
		MODULE_HWEXCEPTION,		// Module caused an hardware exception
	};

	enum loadStatus
	{
		SUCCESS = 0,			// Module successfully loaded
		FAILURE_NOHW,			// The hardware the module relies upon couldn't be detected. Causes a kernel panic.
		FAILURE_NOHW_NOCRASH,	// The hardware the module relies upon couldn't be detected. Doesn't cause a kernel panic if the module can still behave correctly when used.
		FAILURE_NOSW,			// Matching software couldn't be detected. Causes a kernel panic.
		FAILURE_NOSW_NOCRASH,	// Matching software couldn't be detected. Doesn't cause a kernel panic if the module can still behave correctly when used.
	};

	loadstatus load(); // Load and initialize the module
	void free(abortreason r); // Free/quit the module

public:
	const implc* const impl = static_cast<implc*>(this);
};

#include "module.tpp"

#endif