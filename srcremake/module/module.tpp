#include "module.hpp"

template<class implc>
Module<implc>::loadstatus Module<implc>::load()
{
	return impl->load();
}

template<class implc>
void Module<implc>::free(abortreason r)
{
	impl->free(r);
}