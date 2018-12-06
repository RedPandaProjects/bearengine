#include "BearEngine.hpp"

BEARENGINE_API BearEngine::BearEngine*BearEngine::GEngine=0;
extern BearCore::BearMap <BearCore::BearStringConteniar, bsize> *MapName;
extern BearCore::BearMap <bsize, BearCore::BearString> *MapNameID;
extern BearCore::BearMap <BearCore::BearStringAnsiConteniar, BearCore::BearString> *MapType;
void BearEngine::BearEngine::Loop()
{

	if (!GGeneralViewport)return;
	BearCore::BearTimer timer;

	while (GGeneralViewport->Update())
	{
		GGeneralViewport->ClearColor(BearCore::BearColor::Black);
		float time = timer.get_elapsed_time().asseconds();
		timer.restart();
		GGameController->Update(time);
		GConsole->Update(time);
		GLevel->Update(time);
		GGeneralViewport->Swap();
	}
}

void BearEngine::BearEngine::Create(const bchar * name)
{
	BEAR_FATALERROR(!GEngine, TEXT("Двигатель уже создан"));
	BearCore::BearLog::Printf(TEXT("BearEngine build %s"), *BearCore::BearLog::GetBuild(2018, 10, 16));

	BearCore::BearStringPath FSFilePath;
	BearCore::BearFileManager::GetApplicationPath(FSFilePath);

	BearCore::BearString::Contact(FSFilePath, BEAR_PATH);
	BearCore::BearString::Contact(FSFilePath, TEXT(".."));
	BearCore::BearString::Contact(FSFilePath, BEAR_PATH);
	BearCore::BearString::Contact(FSFilePath, TEXT("bear.fs"));

	BearCore::FS = BearCore::bear_new<BearCore::BearFileSystem>();
	BEAR_ERRORMESSAGE(BearCore::FS->LoadFromFile(FSFilePath, BearCore::BearEncoding::UTF8), TEXT("Неудалось загрузить %s"), TEXT("bear.fs"));

	BearCore::BearStringPath content;
	BearCore::BearString::Copy(content, TEXT("content"));
	BearCore::BearString::Contact(content, BEAR_PATH);
	BearCore::BearString::Contact(content, name);

	BearCore::FS->AppendPath(TEXT("%content%"), content, TEXT("%main%"), 1);

	BearCore::BearLog::Printf(TEXT("BearEngine Initialize"));

	MapType= BearCore::bear_new <BearCore::BearMap <BearCore::BearStringAnsiConteniar, BearCore::BearString> >();
	MapName = BearCore::bear_new<BearCore::BearMap <BearCore::BearStringConteniar, bsize> >();
	MapNameID = BearCore::bear_new<BearCore::BearMap <bsize, BearCore::BearString> >();

	{
#define REGISTER_NAME(name,text) N##name=BearName(text);
#include "BearCore/BearNames.h"
	}
	GSystemConfig = BearCore::bear_new<BearCore::BearINI>();
	BearCore::FS->ReadConfig(TEXT("%config%"), TEXT("system.ltx"), *GSystemConfig, BearCore::BearEncoding::UTF8, &GIncluder);
	GGameConfig = BearCore::bear_new<BearCore::BearINI>();
	BearCore::FS->ReadConfig(TEXT("%config%"), TEXT("game.ltx"), *GGameConfig, BearCore::BearEncoding::UTF8, &GIncluder);
	GPlatformConfig = BearCore::bear_new<BearCore::BearINI>();
#ifdef WINDOWS
	BearCore::FS->ReadConfig(TEXT("%config%"), TEXT("windows.ltx"), *GPlatformConfig, BearCore::BearEncoding::UTF8, &GIncluder);
#else LINUX
	BearCore::FS->ReadConfig(TEXT("%config%"), TEXT("linux.ltx"), *GPlatformConfig, BearCore::BearEncoding::UTF8, &GIncluder);
#endif
	GUser = BearCore::bear_new<BearCore::BearINI>();
	BearCore::FS->CreatePath(TEXT("%app_data%"), 0);
	if (BearCore::FS->ExistFile(TEXT("%app_data%"), TEXT("user.ltx")))
		BearCore::FS->ReadConfig(TEXT("%app_data%"), TEXT("user.ltx"), *GUser, BearCore::BearEncoding::UTF8, &GIncluder);
	GObjectManager = BearCore::bear_alloc<BearObjectManager>(1);
	new(GObjectManager)BearObjectManager();

}

void BearEngine::BearEngine::Close()
{
	BearCore::bear_delete(GSystemConfig);
	BearCore::bear_delete(GGameConfig);
	BearCore::bear_delete(GPlatformConfig);
	BearCore::FS->WriteConfig(TEXT("%app_data%"), TEXT("user.ltx"), 0, *GUser, BearCore::BearEncoding::UTF8);
	BearCore::bear_delete(GUser);
	BearCore::bear_delete(MapNameID);
	BearCore::bear_delete(MapName);
	BearCore::bear_delete(MapType);
	BearCore::bear_delete(BearCore::FS);
	GObjectManager->~BearObjectManager();
	BearCore::bear_free(GObjectManager);
}
extern bool GRemakeShaders ;
void BearEngine::BearEngine::Initialize(bchar** ArgV, int32 ArgC)
{
	for (int32 i = 0; i < ArgC; i++)
	{
		if (BearCore::BearString::Compare(ArgV[i], TEXT("-remake_shaders")) == 0)
		{
			GRemakeShaders = true;
		}
	}
	BEAR_OBJECT_VALUE(GGeneralViewport);
	BearGraphics::BearRenderInterface::AttachRenderTargetView(0, *GGeneralViewport);
	BEAR_OBJECT_VALUE(G2DPlane);
	BEAR_OBJECT_VALUE(GInput);
	BEAR_OBJECT_VALUE(GLevel);
	BEAR_OBJECT_VALUE(GGameController);
	BearCore::BearString Level;
	BEAR_OBJECT_VALUE(Level);
	GLevel->Load(*Level);
	GConsole = GObjectManager->Create<BearConsole>(TEXT("BearEngine::BearConsole"));
}

void BearEngine::BearEngine::Destroy()
{
	BEAR_OBJECT_DESTROY(BearEngine);
}

void BearEngine::BearEngine::Update(float time)
{
}

void BearEngine::BearEngine::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearEngine::Load(const BearCore::BearInputStream * stream)
{
}


BearEngine::BearEngine::BearEngine(const BearName&type) :BearObject(type, BO_OnlyOne)
{
	BEAR_OBJECT_VALUE(GRender);
	BEAR_OBJECT_VALUE(GResourceManager);
	
}

BearEngine::BearEngine::~BearEngine()
{
	BearCore::BearLog::Printf(TEXT("BearEngine Destroy"));
	if (GLevel)GLevel->Destroy();
	if (GConsole)GConsole->Destroy();
	if (GGameController)GGameController->Destroy();
	GResourceManager->Destroy();
	if(GGeneralViewport)
	GGeneralViewport->Destroy();
	if (G2DPlane)
		G2DPlane->Destroy();
	if (GInput)GInput->Destroy();

	GRender->Destroy();


}
