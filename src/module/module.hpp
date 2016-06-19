#ifndef HDRIVER
#define HDRIVER

class Module
{
public:
	enum loadResult
	{
		LDSUCCESS = 0, // Success
		LDINITSWFAILURE, // Software failure during initialization.
		LDINITHWFAILURE, // Hardware failure during initialization, if the module is a hardware driver.
		LDNOMATCHINGHW, // Module initialization failed because the module did not detect the hardware it's targeting.
	};

	// Load a kernel module / driver.
	loadResult moduleLoad();

	// Close a module
	void moduleExit();
};

#endif
