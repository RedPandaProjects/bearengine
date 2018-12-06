#pragma once
namespace BearEngine
{
	class BearPhysicsWorld
	{
	public:
		static void Initialize();
		static void Destory();
		static void Update(float time);
	};
}