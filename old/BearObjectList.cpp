#include "BearEngine.hpp"
extern BearCore::BearVector<BearEngine::BearObject*> *ObjectList;
void BearEngine::BearObjectList::Append(BearObject * object)
{
	ObjectList->push_back(object);
}

void BearEngine::BearObjectList::Destroy(BearObject * object)
{
	auto begin = ObjectList->begin();
	auto end = ObjectList->end();
	while (begin != end)
	{
		if (*begin == object)
		{
			object->destroy();
			ObjectList->erase(begin);
		}
		begin++;
	}
}

void BearEngine::BearObjectList::DestroyAll()
{
	auto begin = ObjectList->begin();
	auto end = ObjectList->end();
	while (begin != end)
	{
		(*begin)->destroy();
		begin++;
	}
	ObjectList->clear();
}

BearEngine::BearObject * BearEngine::BearObjectList::Find(const BearName & name)
{
	auto begin = ObjectList->begin();
	auto end = ObjectList->end();
	while (begin != end)
	{
		if ((*begin )->getName() == name)
		{
			return*begin;
		}
		begin++;
	}
	return nullptr;
}
