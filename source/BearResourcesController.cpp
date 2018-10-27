#include "BearEngine.hpp"
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearTexture2D>>*TextureMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearPixelShader>>*PixelShaderMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearVertexShader>>*VertexShaderMap;
void BearEngine::BearResourcesController::Initialize()
{
	TextureMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearTexture2D>>>();
	PixelShaderMap= BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearPixelShader>>>();
	VertexShaderMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearVertexShader>>>();
}
void BearEngine::BearResourcesController::Destory()
{
	BEAR_ASSERT(TextureMap->empty());
	BearCore::bear_delete(TextureMap);
	BEAR_ASSERT(VertexShaderMap->empty());
	BearCore::bear_delete(VertexShaderMap);
	BEAR_ASSERT(PixelShaderMap->empty());
	BearCore::bear_delete(PixelShaderMap);
}