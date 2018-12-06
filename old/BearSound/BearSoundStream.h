#pragma once
namespace BearEngine
{
	class BearSoundStream :public BearResourceWithName
	{
	public:
		BEAR_CLASS_NO_COPY(BearSoundStream);
		static BearSoundStream* Create(const bchar*name);
		void destroy();
	private:
		~BearSoundStream();
		BearSoundStream(const bchar*name);
	};
}