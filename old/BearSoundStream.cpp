#include "BearEngine.hpp"
#include "BearSound.hpp"
extern BearCore::BearFileSystem *FS;
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearSoundStream>>*SoundStreamMap;
BearEngine::BearSoundStream * BearEngine::BearSoundStream::Create(const bchar * name)
{
	auto item = SoundStreamMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == SoundStreamMap->end())
	{
		BearCore::BearDebug::Printf(TEXT("Load sound stream [%s]"), name);
		auto result = BearCore::bear_alloc< BearSoundStream>(1);
		new(result)BearSoundStream(name);
		BearMultiResource<BearSoundStream> obj;
		obj.set(result);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		SoundStreamMap->insert(name, obj);
		return result;
	}
	else
	{
		item->second++;
		return   item->second.get();
	}
}

void BearEngine::BearSoundStream::destroy()
{
	if (get < BearSound::BearSoundStreamOGG >()==0)return;

	auto item = SoundStreamMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != SoundStreamMap->end());
	item->second--;
	if (item->second.empty())
	{
		SoundStreamMap->erase(item);
		BearCore::BearDebug::Printf(TEXT("Unload sound stream[%s]"), get_name());
		BearCore::bear_delete(get < BearSound::BearSoundStreamOGG >());
		get < BearSound::BearSoundStreamOGG >() = 0;
		this->~BearSoundStream();
		BearCore::bear_free(this);
	}

}

BearEngine::BearSoundStream::~BearSoundStream()
{
}

BearEngine::BearSoundStream::BearSoundStream(const bchar * name)
{
	get < BearSound::BearSoundStreamOGG >()= BearCore::bear_new< BearSound::BearSoundStreamOGG>();
	get < BearSound::BearSoundStreamOGG >()->loadFromStream(FS->read(TEXT("%sounds%"), name, TEXT(".ogg")));
}
