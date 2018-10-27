#include "BearEngine.hpp"

BearEngine::BearMaterialInstance::~BearMaterialInstance()
{
	material = 0;
}

void BearEngine::BearMaterialInstance::set()
{
	material->set();
}

bool BearEngine::BearMaterialInstance::suportAlpha()
{
	return false;
}

BearEngine::BearMaterialInstance::BearMaterialInstance(bsize id)
{
	material = BearMaterialController::GetMaterial(id);
}
