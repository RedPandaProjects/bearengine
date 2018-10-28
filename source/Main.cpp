#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
int main()
{
	BearCore::BearMemory::DebugOn();
	BearEngine::BearDevice::Initialize();
	BearEngine::BearRender::Initialize();
	BearEngine::BearResourcesController::Initialize();
	BearEngine::BearMaterialController::Initialize();
	BearEngine::BearPhysicsWorld::Initialize();
//	BearEngine::BearSprite*test = BearEngine::BearSprite::Create(TEXT("ui_test"), false);
	BearEngine::BearGameManager::LoadGame(TEXT("bear_game"));
	BearCore::BearTimer timer;
	//test->getPosition().set(0, 0);
	//test->getSize().set(500, 500);
//	BearEngine::BearObject*obj = BearEngine::GameFactory->createObject("PLAYER");
	BearEngine::BearLevel *level= BearEngine::BearLevel::Create(TEXT("test"));
//	BearEngine::CurrentLevel = &level;
	float time;

	while (BearEngine::BearDevice::Update())
	{
		time = timer.getElapsedTime().asseconds();
		timer.restart();
		if (time < 0.0002f)
			time = 0.0002f;
		BearEngine::BearRender::Clear();
		//test->draw();
	//	obj->update(time);
		BearEngine::BearPhysicsWorld::Update(time);
		level->update(time);
		BearEngine::BearRender::Swap();
		
	}

	BearEngine::BearGameManager::DestroyGame();
	BearEngine::BearPhysicsWorld::Destory();
//	test->destroy();
	level->destroy();
	BearEngine::BearMaterialController::Destory();
	BearEngine::BearResourcesController::Destory();
	BearEngine::BearRender::Destory();
	BearEngine::BearDevice::Destory();
	BearCore::BearProjectTool::Destory();
	BearCore::BearMemory::DebugCheak();
	return 0;
}