#include "BearEngine.hpp"
BEARENGINE_API BearEngine::BearGameController *BearEngine::GGameController = 0;
BearEngine::BearGameController::BearGameController(const BearName & type):BearObject(type,BO_OnlyOne)
{

}

BearEngine::BearGameController::~BearGameController()
{
}

void BearEngine::BearGameController::Destroy()
{
	BEAR_OBJECT_DESTROY(BearGameController);
}

void BearEngine::BearGameController::Update(float time)
{
}

void BearEngine::BearGameController::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearGameController::Load(const BearCore::BearInputStream * stream)
{
}
