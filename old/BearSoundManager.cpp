#include "BearEngine.hpp"
void BearEngine::BearSoundManager::Initialize()
{
	BEAR_FATALERROR(BearSound::BearSoundManager::Initialization(), TEXT("Звук не инцилизирован"));;
}

void BearEngine::BearSoundManager::Destory()
{
	BearSound::BearSoundManager::Close();
}
