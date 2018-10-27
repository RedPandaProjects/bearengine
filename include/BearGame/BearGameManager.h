#pragma once
namespace BearEngine
{
	class BearGameManager
	{
		BEAR_CLASS_STATIC(BearGameManager);
	public:
		static void LoadGame(const bchar*name);
		static void DestroyGame();
	};
}
