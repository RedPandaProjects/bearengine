#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
int main()
{
	BearEngine::BearDevice::Initialize();
	BearEngine::BearRender::Initialize();
	BearEngine::BearResourcesController::Initialize();
	BearEngine::BearPhysicsWorld::Initialize();
	BearCore::BearMemory::DebugOn();
	BearEngine::BearGameManager::LoadGame(TEXT("bear_game"));
	BearCore::BearTimer timer;
//	BearEngine::BearObject*obj = BearEngine::GameFactory->createObject("PLAYER");
	BearEngine::BearLevel level;
	level.load(TEXT("test"));
	BearEngine::CurrentLevel = &level;
	float time;

	while (BearEngine::BearDevice::Update())
	{
		time = timer.getElapsedTime().asseconds();
		timer.restart();
		if (time < 0.0002f)
			time = 0.0002f;
		BearEngine::BearRender::Clear();
	//	obj->update(time);
		BearEngine::BearPhysicsWorld::Update(time);
		level.update(time);
		BearEngine::BearRender::Swap();
		
	}

	BearEngine::BearGameManager::DestroyGame();
	BearEngine::BearPhysicsWorld::Destory();
	BearEngine::BearResourcesController::Destory();
	BearEngine::BearRender::Destory();
	BearEngine::BearDevice::Destory();
	BearCore::BearProjectTool::Destory();
	BearCore::BearMemory::DebugCheak();
	return 0;
}