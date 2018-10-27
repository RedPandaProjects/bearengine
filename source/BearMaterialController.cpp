#include "BearEngine.hpp"
static BearCore::BearMap<bsize,BearCore::BearMemoryRef< BearEngine::BearMaterial>>*VertexShaderMap;
void BearEngine::BearMaterialController::Initialize()
{
	VertexShaderMap = BearCore::bear_new< BearCore::BearMap<bsize, BearCore::BearMemoryRef< BearMaterial>>>();
	BearMaterial *defualt = BearMaterial::Create(TEXT("defualt"), TEXT("default"));
	defualt->appendValue("matrix", BearMaterial::S_Vertex, BearMaterial::ST_Matrix, 0);
	defualt->appendValue("texture", BearMaterial::S_Pixel, BearMaterial::ST_Texture, 1);
	SetMaterial(defualt, MT_Default);
	BearMaterial *sprite = BearMaterial::Create(TEXT("defualt"), TEXT("sprite"));
	sprite->appendValue("matrix", BearMaterial::S_Vertex, BearMaterial::ST_Matrix, 0);
	sprite->appendValue("texture", BearMaterial::S_Pixel, BearMaterial::ST_Texture, 1);
	sprite->appendValue("texture_uv", BearMaterial::S_Vertex, BearMaterial::ST_RGBA, 2);
	SetMaterial(sprite, MT_Sprite);
	BearMaterial *spriteAlpha = BearMaterial::Create(TEXT("alpha"), TEXT("sprite"));
	spriteAlpha->appendValue("matrix", BearMaterial::S_Vertex, BearMaterial::ST_Matrix, 0);
	spriteAlpha->appendValue("texture", BearMaterial::S_Pixel, BearMaterial::ST_Texture, 1);
	spriteAlpha->appendValue("texture_uv", BearMaterial::S_Vertex, BearMaterial::ST_RGBA, 2);
	SetMaterial(spriteAlpha, MT_SpriteAlpha);
}

void BearEngine::BearMaterialController::Destory()
{
	BearCore::bear_delete(VertexShaderMap);
}

BEARENGINE_API void BearEngine::BearMaterialController::SetMaterial(BearMaterial * mat, bsize id)
{
	VertexShaderMap->insert(id, mat);
}

BearEngine::BearMaterial * BearEngine::BearMaterialController::GetMaterial(bsize id)
{
	return *VertexShaderMap->operator[](id);
}
