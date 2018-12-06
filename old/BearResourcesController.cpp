#include "BearEngine.hpp"
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearTexture2D>>*TextureMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearPixelShader>>*PixelShaderMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearVertexShader>>*VertexShaderMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearFont>>*FontMap;
BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearSoundStream>>*SoundStreamMap;
 BearCore::BearVector<BearEngine::BearObject*> *ObjectList;
BearCore::BearMap <BearCore::BearStringConteniar, bsize> *MapName;
void BearEngine::BearResourcesController::Initialize()
{
	TextureMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearTexture2D>>>();
	PixelShaderMap= BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearPixelShader>>>();
	VertexShaderMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearVertexShader>>>();
	FontMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearFont>>>();
	SoundStreamMap = BearCore::bear_new< BearCore::BearMap<BearCore::BearStringConteniar, BearMultiResource<BearSoundStream>>>();
	MapName = BearCore::bear_new<BearCore::BearMap <BearCore::BearStringConteniar, bsize>>();
	ObjectList= BearCore::bear_new<BearCore::BearVector<BearEngine::BearObject*>>();
}
void BearEngine::BearResourcesController::Update(float time)
{
	auto begin = ObjectList->begin();
	auto end = ObjectList->end();
	while (begin != end)
	{
		(*begin)->update(time);
		begin++;
	}
}
void BearEngine::BearResourcesController::Destory()
{
	BEAR_ASSERT(ObjectList->empty());
	BearCore::bear_delete(ObjectList);
	BearCore::bear_delete(MapName);
	BEAR_ASSERT(SoundStreamMap->empty());
	BearCore::bear_delete(SoundStreamMap);
	BEAR_ASSERT(FontMap->empty());
	BearCore::bear_delete(FontMap);
	BEAR_ASSERT(TextureMap->empty());
	BearCore::bear_delete(TextureMap);
	BEAR_ASSERT(VertexShaderMap->empty());
	BearCore::bear_delete(VertexShaderMap);
	BEAR_ASSERT(PixelShaderMap->empty());
	BearCore::bear_delete(PixelShaderMap);
}