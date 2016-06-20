#include "module.hpp"

Module::loadResult Module::moduleLoad() {}
void Module::moduleExit() {}

Module::loadResult ModuleExample::moduleLoad()
{
	return Module::LDSUCCESS;	
}

void ModuleExample::moduleExit()
{

}
