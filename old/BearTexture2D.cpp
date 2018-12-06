#include "BearEngine.hpp"
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearTexture2D>>*TextureMap;


BearEngine::BearTexture2D * BearEngine::BearTexture2D::Create(const bchar * name)
{

	auto item = TextureMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == TextureMap->end())
	{
	
		auto result = BearCore::bear_alloc< BearTexture2D>(1);
		new(result)BearTexture2D(name);
		BearMultiResource<BearTexture2D> obj;
		obj.set(result);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		TextureMap->insert(name, obj);
		return result;
	}
	else
	{
		item->second++;
		return   item->second.get();
	}
}
extern BearCore::BearFileSystem *FS;
#ifdef EDITOR
void BearEngine::BearTexture2D::Compile(const bchar * name)
{
	BearGraphics::BearImage img;
	BearCore::BearDebug::Printf(TEXT("Import texture [%s]"), name);
	img.loadFromStream(**FS->read(TEXT("%import%"), name, TEXT(".tga")));
	img.generateMipmap();
	BearCore::BearStringPath out_path, floder_name;
	FS->updatePath(TEXT("%textures%"), 0, out_path);
	name = BearCore::BearString::ReadTo(name, TEXT("_"), floder_name);
	if (!name[0])
	{
		name = floder_name;

	}
	else
	{
		BearCore::BearString::Contact(out_path, BEAR_PATH);
		BearCore::BearString::Contact(out_path, floder_name);
		if (!BearCore::BearFileManager::DirectoryExists(out_path))
			BEAR_ASSERT(BearCore::BearFileManager::DirectoryCreate(out_path));
	}
	BearCore::BearString::Contact(out_path, BEAR_PATH);
	BearCore::BearString::Contact(out_path, floder_name);
	BearCore::BearString::Contact(out_path, TEXT("_"));
	BearCore::BearString::Contact(out_path, name);
	BearCore::BearString::Contact(out_path, TEXT(".dds"));
	BEAR_ASSERT(img.saveToDds(out_path));
}
#endif
void BearEngine::BearTexture2D::destroy()
{
	if (get<BearGraphics::BearTexture2DRef>() == 0)return;

	auto item = TextureMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != TextureMap->end());
	item->second--;
	if (item->second.empty())
	{
		BearCore::bear_delete(get<BearGraphics::BearTexture2DRef>());
		get<BearGraphics::BearTexture2DRef>() = 0;
		TextureMap->erase(item);
		BearCore::BearDebug::Printf(TEXT("Unload texture [%s]"), get_name());
		this->~BearTexture2D();
		BearCore::bear_free(this);
	}
}

BearEngine::BearTexture2D::~BearTexture2D()
{
	
}


BearEngine::BearTexture2D::BearTexture2D(const bchar * name)
{
	
	BearCore::BearStringPath temp1, temp2;
	temp1[0] = 0;
	BearCore::BearString::ReadTo(name, TEXT('_'), temp2);
	if (temp2[0])
	{
		BearCore::BearString::Contact(temp1, temp2);
		BearCore::BearString::Contact(temp1,BEAR_PATH);
	}

	BearCore::BearString::Contact(temp1, name);
	BearCore::BearString::Contact(temp1, TEXT(".dds"));


	BearGraphics::BearImage img;
	BEAR_ASSERT(img.loadDDSFromStream(**FS->read(TEXT("%textures%"), temp1)));
	BearCore::BearDebug::Printf(TEXT("Load texture [%s] %d kb"), name,int32(img.getSizeInMemory()/1024));
	get < BearGraphics::BearTexture2DRef>() = BearCore::bear_new<BearGraphics::BearTexture2DRef>();
	m_size.set(static_cast<float>(img.getSize().x), static_cast<float>(img.getSize().y));
	get< BearGraphics::BearTexture2DRef>()->create(img, 0, false);
}
