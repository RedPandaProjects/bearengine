#pragma once
namespace BearEngine
{
	
	class BearResourcesController
	{
		BEAR_CLASS_STATIC(BearResourcesController);
	public :
		static void Initialize();
		static void Update(float time);
		static void Destory();
	};
}