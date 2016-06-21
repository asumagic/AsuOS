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

	Module& getModule(int i);
	template <typename T>
	Module* getMatchingModule()
	{
		for (unsigned long i = 0; i < sizeof(modules) / sizeof(*modules); ++i)
		{
			if (T* d = dynamic_cast<T*>(modules[i]))
			{
				return modules[i];
			}
		}
		return nullptr;
	}

	bool  defineISRHandler(uint8_t id, uint64_t addr); // Define an ISR handler address. Returns true if address could be assigned, false if there is a conflict. The module shall 
	uint64_t queryISRHandler(uint8_t id);

private:
	static Kernel* kernel;

public: // temporary until we have dynamic allocation	
	Module* modules[1];
private:

	uint64_t ISRAddressTable[256] = {};
};

#endif
