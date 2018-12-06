#include "BearEngine.hpp"
extern BearCore::BearMap <BearCore::BearStringConteniar, bsize> *MapName;
bsize BearEngine::BearName::GetID(const bchar * name)
{
	auto item = MapName->find(BearCore::BearStringConteniar(name, false));
	if (item == MapName->end())
	{
		MapName->insert(BearCore::BearStringConteniar(name),MapName->size());
		item = MapName->find(BearCore::BearStringConteniar(name, false));
	}
	return item->second;
}
