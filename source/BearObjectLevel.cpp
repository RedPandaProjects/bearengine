#include "BearEngine.hpp"

BearEngine::BearObjectLevel::BearObjectLevel(const BearName & type, uint32 flags):BearObject(type, flags),Rect(0,0,0,0),Name(NNone), Rotation(0)
{
}

BearEngine::BearObjectLevel::~BearObjectLevel()
{
}

void BearEngine::BearObjectLevel::Spawn()
{
}

void BearEngine::BearObjectLevel::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearObjectLevel::Load(const BearCore::BearInputStream * stream)
{
}
