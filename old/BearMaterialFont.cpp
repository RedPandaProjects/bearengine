#include "BearEngine.hpp"

BearEngine::BearMaterialFont * BearEngine::BearMaterialFont::Create()
{
	auto type = BearCore::bear_alloc< BearMaterialFont>(1);
	return	new(type)BearMaterialFont();
}

BearEngine::BearMaterialFont::~BearMaterialFont()
{

}
void BearEngine::BearMaterialFont::destroy()
{
	//Texture->destroy();
	this->~BearMaterialFont();
	BearCore::bear_free(this);
}
BearEngine::BearMaterialFont::BearMaterialFont() :BearMaterialInstance(BearMaterialController::MT_Font)
{
	Texture = 0;
}
void BearEngine::BearMaterialFont::set()
{
	material->setValue(0, Matrix);
	material->setValue(1, Texture);
	material->setValue(2, TextureUV.array);
	__super::set();
}
bool BearEngine::BearMaterialFont::suportAlpha()
{
	return true;
}