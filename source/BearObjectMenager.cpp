#include "BearEngine.hpp"

BearEngine::BearObjectManager::BearObjectManager()
{
	GObjectManager->Registor<BearEngine>();
	GObjectManager->Registor<BearEditor>();
	GObjectManager->Registor<BearRender>();
	GObjectManager->Registor<BearViewport>();
	GObjectManager->Registor<BearResourceManager>();
	GObjectManager->Registor <Bear2DPlane>();
	GObjectManager->Registor <BearSprite>();
	GObjectManager->Registor <BearInput>();
	GObjectManager->Registor <BearRenderText>();
	GObjectManager->Registor <BearSpriteAnimater>();
	GObjectManager->Registor <BearLevel>();
	GObjectManager->Registor <BearTerrain>();
	GObjectManager->Registor < BearTile>();
	GObjectManager->Registor < BearGameController>();
	GObjectManager->Registor < BearConsole>();
	GObjectManager->Registor < BearCallBack>();
}

BearEngine::BearObjectManager::~BearObjectManager()
{
}


BEARENGINE_API BearEngine::BearObjectManager* BearEngine::GObjectManager=0;