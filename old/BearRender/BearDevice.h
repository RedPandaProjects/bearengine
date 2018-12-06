#pragma once
namespace BearEngine
{
	class BearDevice
	{
		BEAR_CLASS_STATIC(BearDevice);
	public:
		static void Initialize();
		static void Destory();
		static const bchar*GetNameGraphics();
		static bool Update();
	};
}