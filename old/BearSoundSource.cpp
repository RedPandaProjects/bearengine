#include "BearEngine.hpp"
BearEngine::BearSoundSource * BearEngine::BearSoundSource::Create(const bchar * name)
{
	return new(BearCore::bear_alloc<BearSoundSource>(1))BearSoundSource(name);
}

void BearEngine::BearSoundSource::play(bool loop)
{
	get<BearSound::BearSoundSource2D>()->play(loop);
}

void BearEngine::BearSoundSource::stop()
{
	get<BearSound::BearSoundSource2D>()->stop();
}

void BearEngine::BearSoundSource::pause()
{
	get<BearSound::BearSoundSource2D>()->pause();
}

void BearEngine::BearSoundSource::destroy()
{
	m_stream->destroy();
	BearCore::bear_delete(get<BearSound::BearSoundSource2D>());
	get<BearSound::BearSoundSource2D>() = 0;
	this->~BearSoundSource();
	BearCore::bear_free(this);
}

BearEngine::BearSoundSource::~BearSoundSource()
{
}

BearEngine::BearSoundSource::BearSoundSource(const bchar * name)
{
	m_stream = BearSoundStream::Create(name);
	get<BearSound::BearSoundSource2D>() = BearCore::bear_new<BearSound::BearSoundSource2D>();
	get<BearSound::BearSoundSource2D>()->setSoundStream(*m_stream->get<BearSound::BearSoundStreamOGG>(),0,true);
}
