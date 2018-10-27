#include "BearEngine.hpp"

BearEngine::BearMaterialDefault * BearEngine::BearMaterialDefault::Create()
{
	auto type = BearCore::bear_alloc< BearMaterialDefault>(1);
	return	new(type)BearMaterialDefault();
}

BearEngine::BearMaterialDefault::~BearMaterialDefault()
{
	BearCore::bear_delete(Texture);
}

BearEngine::BearMaterialDefault::BearMaterialDefault():BearMaterialInstance(BearMaterialController::MT_Default)
{
	Texture = 0;
}

void BearEngine::BearMaterialDefault::set()
{
	material->setValue(0, Matrix);
	material->setValue(1, Texture);
	__super::set();
}
