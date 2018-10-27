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
		obj.get()->get < BearGraphics::BearTexture2DRef>() = result->get < BearGraphics::BearTexture2DRef>();;
		BearCore::BearString::Copy(result->get_name(), 64, name);
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

BearEngine::BearVertexShader::~BearVertexShader()
{
	auto item = VertexShaderMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != VertexShaderMap->end());
	item->second--;
	if (item->second.empty())
		VertexShaderMap->erase(item);
}
static const bchar*ShaderPath = TEXT("..\\..\\content\\stalker2d\\shaders\\dx11\\");

BearEngine::BearVertexShader::BearVertexShader(const bchar * name)
{
	BearCore::BearStringPath temp1;

	BearCore::BearString::Copy(temp1, ShaderPath);
	BearCore::BearString::Contact(temp1, name);
	BearCore::BearString::Contact(temp1, TEXT(".vs"));
	get < BearGraphics::BearVertexShaderRef>() = BearCore::bear_new<BearGraphics::BearVertexShaderRef>();
	BearCore::BearString Error;
	BEAR_ASSERT(get< BearGraphics::BearVertexShaderRef>()->compileFromFile(temp1, BearCore::BearEncoding::UTF8, Error));
}
