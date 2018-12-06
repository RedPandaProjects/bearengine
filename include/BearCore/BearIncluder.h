#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearIncluder :public BearCore::BearIncluder
	{
		BEAR_CLASS_NO_COPY(BearIncluder);
	public:
		BearIncluder();
		virtual BearCore::BearStreamRef<BearCore::BearInputStream> OpenAsStream(const bchar*name);
		virtual BearCore::BearStreamRef<BearCore::BearBufferedReader> OpenAsBuffer(const bchar*name);
		~BearIncluder();
	private:
	
	};
	extern BEARENGINE_API BearIncluder GIncluder;
}