#pragma once
namespace BearEngine
{
	class  BEARENGINE_API BearSoundSource :public BearResource
	{
	public:
		BEAR_CLASS_NO_COPY(BearSoundSource);
		static BearSoundSource* Create(const bchar*name);
		void play(bool loop);
		void stop();
		void pause();
		void destroy();
	private:
		BearSoundStream*m_stream;
		~BearSoundSource();
		BearSoundSource(const bchar*name);
	};
}