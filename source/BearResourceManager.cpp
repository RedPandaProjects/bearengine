#include "BearEngine.hpp"
BEARENGINE_API  BearEngine::BearResourceManager*BearEngine::GResourceManager;
bool GRemakeShaders = false;
BearEngine::BearResourceManager::BearResourceManager(const BearName & type):BearObject(type,BO_OnlyOne)
{

}

BearEngine::BearResourceManager::~BearResourceManager()
{
	BEAR_ASSERT(MapTextures.empty());
	MapTextures.clear();
	BEAR_ASSERT(MapPixelShaders.empty());
	MapPixelShaders.clear();
	BEAR_ASSERT(MapVertexShaders.empty());
	MapVertexShaders.clear();
}

void BearEngine::BearResourceManager::CompilePixelShader(const BearName&name_, bool recompile )
{
	const bchar*name = *name_.to_string();
	if (!BearCore::FS->ExistFile(TEXT("%app_shaders_cur%"), name, TEXT(".ps.bin"))|| GRemakeShaders|| recompile)
	{
		BearCore::BearLog::Printf(TEXT("Compile pixel [%s]"), name);
		BearGraphics::BearShaderPixelCompilerRef compile;
		BearCore::BearString out_error;
		BEAR_ASSERT(compile.CompileFromStream(**BearCore::FS->Read(TEXT("%shaders_cur%"), name, TEXT(".ps")), BearCore::BearEncoding::UTF8, out_error));

		BearCore::BearStringPath file;
		BearCore::FS->UpdatePath(TEXT("%app_shaders_cur%"), 0, file);
		BearCore::BearString::Contact(file, BEAR_PATH);
		BearCore::BearString::Contact(file, name);
		BearCore::BearString::Contact(file, TEXT(".ps.bin"));
		compile.SaveToFile(file);
	}
}

void BearEngine::BearResourceManager::CompileVertexShader(const BearName&name_, bool recompile)
{
	const bchar*name = *name_.to_string();
	if (!BearCore::FS->ExistFile(TEXT("%app_shaders_cur%"), name, TEXT(".vs.bin"))|| GRemakeShaders || recompile)
	{
		BearCore::BearLog::Printf(TEXT("Compile pixel [%s]"), name);
		BearGraphics::BearShaderVertexCompilerRef compile;
		BearCore::BearString out_error;
		BEAR_ASSERT(compile.CompileFromStream(**BearCore::FS->Read(TEXT("%shaders_cur%"), name, TEXT(".vs")), BearCore::BearEncoding::UTF8, out_error));

		BearCore::BearStringPath file;
		BearCore::FS->UpdatePath(TEXT("%app_shaders_cur%"), 0, file);
		BearCore::BearString::Contact(file, BEAR_PATH);
		BearCore::BearString::Contact(file, name);
		BearCore::BearString::Contact(file, TEXT(".vs.bin"));
		compile.SaveToFile(file);
	}
}

BearEngine::BearAnimateArray2DRef * BearEngine::BearResourceManager::GetAnimateArray2D(const BearName & name)
{
	auto item = MapAnimation2DArray.find(name);
	if (item == MapAnimation2DArray.end())
	{
		MapAnimation2DArray.insert(name);
		item = MapAnimation2DArray.find(name);
	}
	if (item->second.empty())
	{
		item->second.get()->copy(BearAnimateArray2D(*name.to_string()));
	}
	auto resource = new(BearCore::bear_alloc<BearAnimateArray2DRef>(1))BearAnimateArray2DRef(name, item->second);
	return resource;
}

void BearEngine::BearResourceManager::Destroy(BearAnimateArray2DRef *& anim)
{
	anim->m_resource.clear();
	auto item = MapAnimation2DArray.find(anim->get_name());
	if (item->second.is_one())
	{
		MapAnimation2DArray.erase(item);
		BearCore::BearLog::Printf(TEXT("Unload font [%s]"), *anim->get_name().to_string());
	}
	anim->~BearResource();
	BearCore::bear_free(anim);
}

BearEngine::BearFontRef * BearEngine::BearResourceManager::GetFont(const BearName & name)
{
	auto item = MapFonts.find(name);
	if (item == MapFonts.end())
	{
		MapFonts.insert(name);
		item = MapFonts.find(name);
	}
	if (item->second.empty())
	{
		item->second.get()->copy( BearFont(*name.to_string()));
	}
	auto resource = new(BearCore::bear_alloc<BearFontRef>(1))BearFontRef(name, item->second);
	return resource;
}

void BearEngine::BearResourceManager::Destroy(BearFontRef *& font)
{
	font->m_resource.clear();
	auto item = MapFonts.find(font->get_name());
	if (item->second.is_one())
	{
		MapFonts.erase(item);
		BearCore::BearLog::Printf(TEXT("Unload font [%s]"), *font->get_name().to_string());
	}
	font->~BearResource();
	BearCore::bear_free(font);
}

BearEngine::BearTexture2DRef* BearEngine::BearResourceManager::GetTexture2D(const BearName&name)
{
	auto item = MapTextures.find(name);
	if (item == MapTextures.end())
	{
		MapTextures.insert(name);
		item = MapTextures.find(name);
	}
	if (item->second.Empty())
	{
		LoadTexture(item->second, *name.to_string());
	}
	auto resource = new(BearCore::bear_alloc<BearTexture2DRef>(1))BearTexture2DRef(name, item->second);
	return resource;
}

void BearEngine::BearResourceManager::Destroy(BearTexture2DRef *& texture)
{
	texture->m_resource.Clear();
	auto item = MapTextures.find(texture->get_name());
	if (item->second.IsOne())
	{
		MapTextures.erase(item);
		BearCore::BearLog::Printf(TEXT("Unload texture [%s]"), *texture->get_name().to_string());
	}
	texture->~BearResource();
	BearCore::bear_free(texture);
}

BearEngine::BearPixelShaderRef * BearEngine::BearResourceManager::GetPixelShader(const BearName & name)
{
	auto item = MapPixelShaders.find(name);
	if (item == MapPixelShaders.end())
	{
		MapPixelShaders.insert(name);
		item = MapPixelShaders.find(name);
	}
	if (item->second.Empty())
	{
		LoadShaderPixel(item->second, *name.to_string());
	}
	auto resource = new(BearCore::bear_alloc<BearPixelShaderRef>(1))BearPixelShaderRef(name, item->second);
	return resource;
}

void BearEngine::BearResourceManager::Destroy(BearPixelShaderRef *& texture)
{
	texture->m_resource.Clear();
	auto item = MapPixelShaders.find(texture->get_name());
	if (item->second.IsOne())
	{
		MapPixelShaders.erase(item);
		BearCore::BearLog::Printf(TEXT("Unload shader [%s]"), *texture->get_name().to_string());
	}
	texture->~BearResource();
	BearCore::bear_free(texture);
}

BearEngine::BearVertexShaderRef * BearEngine::BearResourceManager::GetVertexShader(const BearName & name)
{
	auto item = MapVertexShaders.find(name);
	if (item == MapVertexShaders.end())
	{
		MapVertexShaders.insert(name);
		item = MapVertexShaders.find(name);
	}
	if (item->second.Empty())
	{
		LoadShaderVertex(item->second, *name.to_string());
	}
	auto resource = new(BearCore::bear_alloc<BearVertexShaderRef>(1))BearVertexShaderRef(name, item->second);
	return resource;
}

void BearEngine::BearResourceManager::Destroy(BearVertexShaderRef *& texture)
{
	texture->m_resource.Clear();
	auto item = MapVertexShaders.find(texture->get_name());
	if (item->second.IsOne())
	{
		MapVertexShaders.erase(item);
		BearCore::BearLog::Printf(TEXT("Unload shader [%s]"), *texture->get_name().to_string());
	}
	texture->~BearResource();
	BearCore::bear_free(texture);
}

void BearEngine::BearResourceManager::RecompileShaders()
{
	GRender->ClearStats();
	{
		auto begin = MapVertexShaders.begin();
		auto end = MapVertexShaders.end();
		while (begin != end)
		{
			LoadShaderVertex(begin->second, *begin->first.to_string(),true);
			begin++;
		}
	}
	{
		auto begin = MapPixelShaders.begin();
		auto end = MapPixelShaders.end();
		while (begin != end)
		{
			LoadShaderPixel(begin->second, *begin->first.to_string() ,true);
			begin++;
		}
	}
}

void BearEngine::BearResourceManager::ReloadTextures()
{
	auto begin=MapTextures.begin();
	auto end = MapTextures.end();
	while (begin != end)
	{
		LoadTexture(begin->second, *begin->first.to_string());
		begin++;
	}
}


void BearEngine::BearResourceManager::Destroy()
{
	BEAR_OBJECT_DESTROY(BearResourceManager);
}

void BearEngine::BearResourceManager::LoadTexture(BearGraphics::BearTexture2DRef & ref, const bchar * name_str)
{
	BearCore::BearStringPath temp1, temp2;
	temp1[0] = 0;
	;
	if (BearCore::BearString::ReadTo(name_str, TEXT('_'), temp2)[0])
	{
		BearCore::BearString::Contact(temp1, temp2);
		BearCore::BearString::Contact(temp1, BEAR_PATH);
	}

	BearCore::BearString::Contact(temp1, name_str);
	BearCore::BearString::Contact(temp1, TEXT(".dds"));

	BearGraphics::BearImage img;
	BEAR_ASSERT(img.LoadDDSFromStream(**BearCore::FS->Read(TEXT("%textures%"), temp1)));
	BearCore::BearLog::Printf(TEXT("Load texture [%s] %d kb"), name_str, int32(img.GetSizeInMemory() / 1024));
	ref.Create(img);
}

void BearEngine::BearResourceManager::LoadShaderVertex(BearGraphics::BearVertexShaderRef & ref, const bchar * name, bool recompile)
{
	CompileVertexShader(name, recompile);
	BearCore::BearLog::Printf(TEXT("Load vertex shader [%s]"), name);
	ref.LoadFromStream(**BearCore::FS->Read(TEXT("%app_shaders_cur%"), name, TEXT(".vs.bin")));
}

void BearEngine::BearResourceManager::LoadShaderPixel(BearGraphics::BearPixelShaderRef & ref, const bchar * name, bool recompile)
{
	CompilePixelShader(name, recompile);
	BearCore::BearLog::Printf(TEXT("Load pixel shader [%s]"), name);
	ref.LoadFromStream(**BearCore::FS->Read(TEXT("%app_shaders_cur%"), name, TEXT(".ps.bin")));
}

void BearEngine::BearResourceManager::Update(float time)
{
}

void BearEngine::BearResourceManager::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearResourceManager::Load(const BearCore::BearInputStream * stream)
{
}
