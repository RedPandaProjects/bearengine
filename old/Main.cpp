#include "BearEngine.hpp"
#define GAME TEXT("stalker2D")
BearCore::BearFileSystem *FS = NULL;
bool bEditor = false;
bool bRecompileShader = false;
void destroy()
{
	BearCore::BearDebug::DebugPrintf(TEXT("Destroy engine"));
	BearEngine::GameFactory->destroy();

	BearEngine::BearGameManager::DestroyGame();
	BearEngine::BearPhysicsWorld::Destory();
	BearEngine::BearMaterialController::Destory();
	BearEngine::BearResourcesController::Destory();
	BearEngine::BearSoundManager::Destory();
	BearEngine::BearRender::Destory();
	BearEngine::BearShaderManager::Destroy();
	BearEngine::BearDevice::Destory();
	BearCore::BearProjectTool::Destory();
	BearCore::bear_delete(FS);
	BearCore::BearDebug::Destroy();
	BearCore::BearMemory::DebugCheak();
}
void initialize()
{
	BearCore::BearDebug::DebugPrintf(TEXT("Initialize engine"));
	BearEngine::BearDevice::Initialize();
	BearEngine::BearShaderManager::Initialize();
	BearEngine::BearRender::Initialize();
	BearEngine::BearResourcesController::Initialize();
	BearEngine::BearMaterialController::Initialize();
	BearEngine::BearPhysicsWorld::Initialize();
	BearEngine::BearSoundManager::Initialize();

	//	BearEngine::BearSprite*test = BearEngine::BearSprite::Create(TEXT("ui_test"), false);
	BearEngine::BearGameManager::LoadGame(GAME);

	BearCore::BearStringPath content;
	BearCore::BearString::Copy(content, TEXT("content"));
	BearCore::BearString::Contact(content, BEAR_PATH);
	BearCore::BearString::Contact(content, BearEngine::GameFactory->getGameName());
	FS->appendPath(TEXT("%content%"), content, TEXT("%main%"), 1);

	BearEngine::GameFactory->initialize();
}
#ifdef EDITOR 
void initializeForEditor()
{
	bEditor = true;
	BearCore::BearDebug::DebugPrintf(TEXT("Initialize engine for editor"));
	BearEngine::BearDevice::Initialize();
	BearEngine::BearResourcesController::Initialize();
	BearEngine::BearGameManager::LoadGame(GAME);

	BearCore::BearStringPath content;
	BearCore::BearString::Copy(content, TEXT("content"));
	BearCore::BearString::Contact(content, BEAR_PATH);
	BearCore::BearString::Contact(content, BearEngine::GameFactory->getGameName());
	FS->appendPath(TEXT("%content%"), content, TEXT("%main%"), 1);

	BearEngine::GameFactory->initialize();
}
void destroyForEditor()
{
	BearCore::BearDebug::DebugPrintf(TEXT("Destroy engine"));
	BearEngine::GameFactory->destroy();
	BearEngine::BearGameManager::DestroyGame();
	BearEngine::BearDevice::Destory();
	BearEngine::BearResourcesController::Destory();
	BearCore::BearProjectTool::Destory();
	BearCore::bear_delete(FS);
	BearCore::BearDebug::Destroy();
	BearCore::BearMemory::DebugCheak();
}

void editor(int32 ArgC, TCHAR* ArgV[])
{
	for (int32 i = 0; i < ArgC; i++)
	{
		if (BearCore::BearString::Compare(ArgV[i], TEXT("-import_texture")) == 0)
		{
			initializeForEditor();
			BearCore::BearVector<BearCore::BearString> textures;
			FS->getFiles(textures, TEXT("%import%"), TEXT("*.tga"));
			auto begin = textures.begin();
			auto end = textures.end();
			while (begin != end)
			{
				BearEngine::BearTexture2D::Compile(*BearCore::BearFileManager::GetFileName(**begin));
				BearCore::BearStringPath file, new_file;
				FS->update(TEXT("%import%"), **begin, file);
				BearCore::BearString::Copy(new_file, file);
				BearCore::BearString::Contact(new_file, TEXT(".old"));
				BearCore::BearFileManager::FileMove(file, new_file);
				begin++;
			}
			destroyForEditor();
			exit(0);
		}
		else if (BearCore::BearString::Compare(ArgV[i], TEXT("-import_anim")) == 0 && i + 1 < ArgC)
		{
			initializeForEditor();
			BearEngine::BearSpriteAnimated::Compile(ArgV[++i]);
			destroyForEditor();
			exit(0);
		}
		else if (BearCore::BearString::Compare(ArgV[i], TEXT("-compile")) == 0 && i + 1 < ArgC)
		{
			initializeForEditor();
			BearEngine::BearLevel::Compile(ArgV[++i]);
			destroyForEditor();
			exit(0);
		}
		else if (BearCore::BearString::Compare(ArgV[i], TEXT("-import_font")) == 0 && i + 1 < ArgC)
		{
			initializeForEditor();
			BearEngine::BearFont::Compile(ArgV[++i]);
			destroyForEditor();
			exit(0);
		}
		else if (BearCore::BearString::Compare(ArgV[i], TEXT("-recompile_shader")) == 0)
		{
			bRecompileShader = true;
		}
	}
}
#else
void editor(int32 ArgC, TCHAR* ArgV[])
{ }
#endif

int wmain(int32 ArgC, TCHAR* ArgV[])
{
	
	BearCore::BearMemory::DebugOn();
	BearCore::BearDebug::Initialize(TEXT("log.txt"), true);
	BearCore::BearDebug::Printf(TEXT("BearEngine build %s"), *BearCore::BearDebug::GetBuild(2018, 10, 16));

	BearCore::BearStringPath FSFilePath;
	BearCore::BearFileManager::GetApplicationPath(FSFilePath);

	BearCore::BearString::Contact(FSFilePath, BEAR_PATH);
	BearCore::BearString::Contact(FSFilePath, TEXT(".."));
	BearCore::BearString::Contact(FSFilePath, BEAR_PATH);
	BearCore::BearString::Contact(FSFilePath, TEXT("bear.fs"));

	FS = BearCore::bear_new<BearCore::BearFileSystem>();
	BEAR_ERRORMESSAGE(FS->loadFromFile(FSFilePath, BearCore::BearEncoding::UTF8), TEXT("Неудалось загрузить %s"),TEXT("bear.fs"));
	


	editor(ArgC, ArgV);

	initialize();

	BearCore::BearTimer timer;
	BearEngine::BearLevel *level = BearEngine::BearLevel::Create(TEXT("test_view"));
	float time;
	BearCore::BearDebug::DebugPrintf(TEXT("Start engine"));
	while (BearEngine::BearDevice::Update())
	{
		time = timer.getElapsedTime().asseconds();
		timer.restart();
		if (time < 0.0002f)
			time = 0.0002f;
		BearEngine::BearRender::Clear();
		BearEngine::BearPhysicsWorld::Update(time);
		level->update(time);
		BearEngine::BearResourcesController::Update(time);
		BearEngine::BearRender::Swap();
	}
	level->destroy();
	destroy();
	return 0;
}