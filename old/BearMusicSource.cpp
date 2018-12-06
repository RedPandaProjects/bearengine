#include "BearEngine.hpp"


BearEngine::BearMusicSource * BearEngine::BearMusicSource::Create(const bchar * name)
{
	return new(BearCore::bear_alloc<BearMusicSource>(1))BearMusicSource(name);
}

void BearEngine::BearMusicSource::play(bool loop)
{
	get<BearSound::BearSoundSource2D>()->play(loop);
}

void BearEngine::BearMusicSource::stop()
{
	get<BearSound::BearSoundSource2D>()->stop();
}

void BearEngine::BearMusicSource::pause()
{
	get<BearSound::BearSoundSource2D>()->pause();
}

void BearEngine::BearMusicSource::update()
{
	get<BearSound::BearSoundSource2D>()->update();
}

void BearEngine::BearMusicSource::destroy()
{
	m_stream->destroy();
	BearCore::bear_delete(get<BearSound::BearSoundSource2D>());
	get<BearSound::BearSoundSource2D>() = 0;
	this->~BearMusicSource();
	BearCore::bear_free(this);
}

BearEngine::BearMusicSource::~BearMusicSource()
{
}

BearEngine::BearMusicSource::BearMusicSource(const bchar * name)
{
	m_stream = BearSoundStream::Create(name);
	get<BearSound::BearSoundSource2D>() = BearCore::bear_new<BearSound::BearSoundSource2D>();
	get<BearSound::BearSoundSource2D>()->setSoundStream(*m_stream->get<BearSound::BearSoundStreamOGG>(), 0, false);
}
