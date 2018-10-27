#include "BearEngine.hpp"

BearEngine::BearMaterialInstance::~BearMaterialInstance()
{
	material = 0;
}

void BearEngine::BearMaterialInstance::set()
{
	material->set();
}

BearEngine::BearMaterialInstance::BearMaterialInstance(bsize id)
{
	material = BearMaterialController::GetMaterial(id);
}
