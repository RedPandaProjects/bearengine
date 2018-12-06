#include "BearEngine.hpp"

BearEngine::BearMaterialDefault * BearEngine::BearMaterialDefault::Create()
{
	auto type = BearCore::bear_alloc< BearMaterialDefault>(1);
	return	new(type)BearMaterialDefault();
}

BearEngine::BearMaterialDefault::~BearMaterialDefault()
{

}

void BearEngine::BearMaterialDefault::destroy()
{
	Texture->destroy();
	this->~BearMaterialDefault();
	BearCore::bear_free(this);
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
