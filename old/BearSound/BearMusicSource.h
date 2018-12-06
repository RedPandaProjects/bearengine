#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearMusicSource :public BearResource
	{
	public:
		BEAR_CLASS_NO_COPY(BearMusicSource);
		static BearMusicSource* Create(const bchar*name);
		void play(bool loop);
		void stop();
		void pause();
		void update();
		void destroy();
	private:
		BearSoundStream*m_stream;
		~BearMusicSource();
		BearMusicSource(const bchar*name);
	};
}