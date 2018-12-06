#include "BearEngine.hpp"

BearEngine::BearMaterialSprite * BearEngine::BearMaterialSprite::Create()
{
	auto type = BearCore::bear_alloc< BearMaterialSprite>(1);
	return	new(type)BearMaterialSprite();
}

BearEngine::BearMaterialSprite::~BearMaterialSprite()
{

}
void BearEngine::BearMaterialSprite::destroy()
{
	Texture->destroy();
	this->~BearMaterialSprite();
	BearCore::bear_free(this);
}
BearEngine::BearMaterialSprite::BearMaterialSprite() :BearMaterialInstance(BearMaterialController::MT_Sprite)
{
	Texture = 0;
}
void BearEngine::BearMaterialSprite::set()
{
	material->setValue(0, Matrix);
	material->setValue(1, Texture);
	material->setValue(2, TextureUV.array);
	__super::set();
}
