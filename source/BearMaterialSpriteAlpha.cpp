#include "BearEngine.hpp"

BearEngine::BearMaterialSpriteAlpha * BearEngine::BearMaterialSpriteAlpha::Create()
{
	auto type = BearCore::bear_alloc< BearMaterialSpriteAlpha>(1);
	return	new(type)BearMaterialSpriteAlpha();
}

BearEngine::BearMaterialSpriteAlpha::~BearMaterialSpriteAlpha()
{

}
BearEngine::BearMaterialSpriteAlpha::BearMaterialSpriteAlpha() :BearMaterialInstance(BearMaterialController::MT_Sprite)
{
	Texture = 0;
}
bool BearEngine::BearMaterialSpriteAlpha::suportAlpha()
{
	return true;
}
void BearEngine::BearMaterialSpriteAlpha::destroy()
{
	Texture->destroy();
	this->~BearMaterialSpriteAlpha();
	BearCore::bear_free(this);
}
void BearEngine::BearMaterialSpriteAlpha::set()
{
	material->setValue(0, Matrix);
	material->setValue(1, Texture);
	material->setValue(2, TextureUV.array);
	__super::set();
}
