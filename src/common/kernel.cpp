#include "kernel.hpp"

Kernel* Kernel::kernel;

Kernel::Kernel()
{
	kernel = this;
}

Kernel* Kernel::getObject()
{
	return kernel;
}

void Kernel::initializeModules()
{
	for (unsigned long i = 0; i < sizeof(modules) / sizeof(*modules); ++i)
	{
		modules[i]->moduleLoad();
	}
}

Module& Kernel::getModule(int i)
{
	return *modules[i];
}

bool Kernel::defineISRHandler(uint8_t id, uint64_t addr)
{
	if (!ISRAddressTable[id])
	{
		ISRAddressTable[id] = addr;
		return true;
	}

	return false;
}

uint64_t Kernel::queryISRHandler(uint8_t id)
{
	return ISRAddressTable[id];
}
