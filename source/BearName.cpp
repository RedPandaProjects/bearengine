#include "BearEngine.hpp"
BearCore::BearMap <BearCore::BearStringConteniar, bsize> *MapName=0;
BearCore::BearMap <bsize, BearCore::BearString> *MapNameID = 0;
bsize BearEngine::BearName::GetID(const bchar * name)
{
	auto item = MapName->find(BearCore::BearStringConteniar(name, false));
	if (item == MapName->end())
	{
		MapNameID->insert(MapName->size(),name);
		MapName->insert(BearCore::BearStringConteniar(name),MapName->size());
		item = MapName->find(BearCore::BearStringConteniar(name, false));
	}
	return item->second;
}

const BearCore::BearString & BearEngine::BearName::GetString(bsize id)
{
	auto item = MapNameID->find(id);
	BEAR_ASSERT(id);
	return item->second;

}
#define REGISTER_NAME(name,text) BEARENGINE_API    BearEngine::BearName  BearEngine::N##name;
#include "BearCore/BearNames.h"