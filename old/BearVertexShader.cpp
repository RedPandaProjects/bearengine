#include "BearEngine.hpp"
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearVertexShader>>*VertexShaderMap;
BearEngine::BearVertexShader * BearEngine::BearVertexShader::Create(const bchar * name)
{
	auto item = VertexShaderMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == VertexShaderMap->end())
	{

		auto result = BearCore::bear_alloc< BearVertexShader>(1);
		new(result)BearVertexShader(name);
		BearMultiResource<BearVertexShader> obj;
		obj.set( result);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		VertexShaderMap->insert(name, obj);
		return result;
	}
	else
	{
		item->second++;
		return   item->second.get();
	}
}

void BearEngine::BearVertexShader::destroy()
{
	if (get<BearGraphics::BearVertexShaderRef>() == 0)return;
	auto item = VertexShaderMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != VertexShaderMap->end());
	item->second--;
	if (item->second.empty())
	{
		BearCore::bear_delete(get<BearGraphics::BearVertexShaderRef>());
		get<BearGraphics::BearVertexShaderRef>() = 0;
		VertexShaderMap->erase(item);
		BearCore::BearDebug::Printf(TEXT("Unload vertex shader [%s]"), get_name());
		this->~BearVertexShader();
		BearCore::bear_free(this);
	}
	
}


BearEngine::BearVertexShader::~BearVertexShader()
{
}
extern BearCore::BearFileSystem *FS;
BearEngine::BearVertexShader::BearVertexShader(const bchar * name)
{
	BearShaderManager::CompileVertexShader(name);
	BearCore::BearDebug::Printf(TEXT("Load vertex shader [%s]"), name);

	get < BearGraphics::BearVertexShaderRef>() = BearCore::bear_new<BearGraphics::BearVertexShaderRef>();
	BearCore::BearString Error;
	BEAR_ASSERT(get< BearGraphics::BearVertexShaderRef>()->loadFromStream(**FS->read(TEXT("%app_shaders_cur%"), name, TEXT(".vs.bin"))));
}
