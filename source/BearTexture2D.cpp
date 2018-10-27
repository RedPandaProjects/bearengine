#include "BearEngine.hpp"
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearTexture2D>>*TextureMap;

static const bchar*TexturePath = TEXT("..\\..\\content\\stalker2d\\textures\\");

BearEngine::BearTexture2D * BearEngine::BearTexture2D::Create(const bchar * name)
{

	auto item = TextureMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == TextureMap->end())
	{
	
		BearTexture2D* result = BearCore::bear_new<BearTexture2D>(name);
		BearMultiResource<BearTexture2D> obj;
		obj.get()->get < BearGraphics::BearTexture2DRef>() = result->get < BearGraphics::BearTexture2DRef>();;
		BearCore::BearString::Copy(result->get_name(), 64, name);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		TextureMap->insert(name, obj);
		return result;
	}
	else
	{
		BearTexture2D* result;
		item->second++;
		return   *item->second.get();
	}
}

BearEngine::BearTexture2D::~BearTexture2D()
{
	auto item = TextureMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != TextureMap->end());
	item->second--;
	if(item->second.empty())
	TextureMap->erase(item);
}

BearCore::BearVector2<float> BearEngine::BearTexture2D::getSize() const
{
	return BearCore::BearVector2<float>();
}

BearEngine::BearTexture2D::BearTexture2D(const bchar * name)
{
	BearCore::BearStringPath temp1, temp2;
	BearCore::BearString::Copy(temp1, TexturePath);

	BearCore::BearString::ReadTo(name, TEXT('_'), temp2);
	if (temp2[0])
	{
		BearCore::BearString::Contact(temp1, temp2);
		BearCore::BearString::Contact(temp1, TEXT("\\"));
	}

	BearCore::BearString::Contact(temp1, name);
	BearCore::BearString::Contact(temp1, TEXT(".dds"));
	BearGraphics::BearImage img;
	BEAR_ASSERT(img.loadDDSFromFile(temp1));
	get < BearGraphics::BearTexture2DRef>() = BearCore::bear_new<BearGraphics::BearTexture2DRef>();
	get< BearGraphics::BearTexture2DRef>()->create(img, 0, false);
}
