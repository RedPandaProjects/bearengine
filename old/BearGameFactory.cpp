#include "BearEngine.hpp"
BEARENGINE_API BearEngine::BearGameFactory * BearEngine::GameFactory = NULL;

void BearEngine::BearGameFactory::initialize()
{
}

void BearEngine::BearGameFactory::destroy()
{
	objects.clear();
}

BearEngine::BearObject * BearEngine::BearGameFactory::getObject(const BearObjectType & type)
{
	auto item=objects.find(type);
	BEAR_ASSERT(item != objects.end());
	return item->second;
}

const bchar * BearEngine::BearGameFactory::getGameName()
{
	return TEXT("engine");
}
