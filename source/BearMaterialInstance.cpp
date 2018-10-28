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

void BearEngine::BearMaterialInstance::destroy()
{
	this->~BearMaterialInstance();
	BearCore::bear_free(this);
}

BearEngine::BearMaterialInstance::BearMaterialInstance(bsize id)
{
	material = BearMaterialController::GetMaterial(id);
}
