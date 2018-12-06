#include "BearEngine.hpp"
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearPixelShader>>*PixelShaderMap;
BearEngine::BearPixelShader * BearEngine::BearPixelShader::Create(const bchar * name)
{
	auto item = PixelShaderMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == PixelShaderMap->end())
	{
		auto result = BearCore::bear_alloc< BearPixelShader>(1);
		new(result)BearPixelShader(name);
		BearMultiResource<BearPixelShader> obj;
		obj.set(result);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		PixelShaderMap->insert(name, obj);
		return result;
	}
	else
	{
		item->second++;
		return   item->second.get();
	}
}

void BearEngine::BearPixelShader::destroy()
{
	if (get<BearGraphics::BearPixelShaderRef>() == 0)return;
	auto item = PixelShaderMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != PixelShaderMap->end());
	item->second--;
	if (item->second.empty())
	{
		BearCore::bear_delete(get<BearGraphics::BearPixelShaderRef>());
		get<BearGraphics::BearPixelShaderRef>() = 0;
		PixelShaderMap->erase(item);
		BearCore::BearDebug::Printf(TEXT("Unload pixel shader [%s]"), get_name());
		this->~BearPixelShader();
		BearCore::bear_free(this);
	}
	
}

BearEngine::BearPixelShader::~BearPixelShader()
{

}
extern BearCore::BearFileSystem *FS;
BearEngine::BearPixelShader::BearPixelShader(const bchar * name)
{
	BearShaderManager::CompilePixelShader(name);
	BearCore::BearDebug::Printf(TEXT("Load pixel shader [%s]"), name);
	get < BearGraphics::BearPixelShaderRef>() = BearCore::bear_new<BearGraphics::BearPixelShaderRef>();
	BearCore::BearString Error;
	BEAR_ASSERT(get< BearGraphics::BearPixelShaderRef>()->loadFromStream(**FS->read(TEXT("%app_shaders_cur%"), name, TEXT(".ps.bin"))));
}
