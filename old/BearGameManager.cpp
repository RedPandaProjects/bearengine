#include "BearEngine.hpp"
static void(*GameDestroyFunction)(void);
void BearEngine::BearGameManager::LoadGame(const bchar * name)
{
	BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("Initialize"))();
	GameDestroyFunction = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("Destroy"));
}

void BearEngine::BearGameManager::DestroyGame()
{
	GameDestroyFunction();
}
