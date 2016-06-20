#ifndef HKERNEL
#define HKERNEL

#include "../module/module.hpp"
#include <stdint.h>

class Kernel
{
public:
	Kernel();

	static Kernel* getObject();

	void initializeModules();

	void defineISRHandler(uint8_t id, uint64_t addr);
	uint64_t queryISRHandler(uint8_t id);

private:
	static Kernel* kernel;

public: // temporary until we have dynamic allocation	
	Module* modules[1];
private:

	uint64_t ISRAddressTable[256] = {};
};

#endif
