#include "BearEngine.hpp"

BearEngine::BearConsoleCommand::~BearConsoleCommand()
{
}

bool BearEngine::BearConsoleCommand::Execute(const bchar * command)
{
	return false;
}

void BearEngine::BearConsoleCommand::Destroy()
{
	BEAR_OBJECT_DESTROY(BearConsoleCommand);
}

void BearEngine::BearConsoleCommand::Info()
{
	BearCore::BearLog::Printf(TEXT("%s"), *m_info);
}

void BearEngine::BearConsoleCommand::Status()
{
}

class BCC_Version :public BearEngine::BearConsoleCommand
{
public:
	BCC_Version() :BearConsoleCommand(TEXT("version"), TEXT("(no argumet)"),true){}
	~BCC_Version() {}
	virtual bool Execute(const bchar*argv)
	{
		BearCore::BearLog::Printf(TEXT("BearEngine build %s"), *BearCore::BearLog::GetBuild(2018, 10, 16));
		return true;
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_Version);
	}
};

class BCC_VideoMode :public BearEngine::BearConsoleCommand
{
public:
	BCC_VideoMode() :BearConsoleCommand(TEXT("video_mode"), TEXT("Set size screen [Widht]x[Height]"),false,true) {}
	~BCC_VideoMode() {}
	virtual void Status()
	{
		BearCore::BearLog::Printf(TEXT("Size screen is %dx%d"),BearEngine::GRender->GetSize().x, BearEngine::GRender->GetSize().y);
	}
	virtual bool Execute(const bchar*argv)
	{
		uint32 w, h;
		if (BearCore::BearString::Scanf(argv, TEXT("%ux%u"), &w, &h) == 2)
		{
			BearEngine::GRender->Resize(static_cast<bsize>(w), static_cast<bsize>(h));
			return true;
		}
		else
		{
			BearCore::BearLog::Printf(TEXT("? Wrong size screen [%s])"), argv);
			return false;
		}
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_VideoMode);
	}
};
extern bool GExit;
class BCC_Quit :public BearEngine::BearConsoleCommand
{
public:
	BCC_Quit() :BearConsoleCommand(TEXT("quit"), TEXT("exit to os"), true, true) {}
	~BCC_Quit() {}
	virtual void Status()
	{
	//	BearCore::BearLog::Printf(TEXT("Size screen is %dx%d"), BearEngine::GRender->GetSize().x, BearEngine::GRender->GetSize().y);
	}
	virtual bool Execute(const bchar*argv)
	{
		GExit = true;
		return true;
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_Quit);
	}
};
class BCC_LevelOpen :public BearEngine::BearConsoleCommand
{
public:
	BCC_LevelOpen() :BearConsoleCommand(TEXT("level_open"), TEXT("level open [name]"), false,true) {}
	~BCC_LevelOpen() {}
	virtual void Status()
	{
		BearCore::BearLog::Printf(TEXT("level name is %s"), *BearEngine::GLevel->GetString());
	}
	virtual bool Execute(const bchar*argv)
	{
		BearCore::BearStringPath level_name;
		if (BearCore::BearString::Scanf(argv, TEXT("%s"), level_name) == 1)
		{
			BearEngine::GLevel->Load(level_name);
			return true;
		}
		else
		{
			BearCore::BearLog::Printf(TEXT("? Wrong level name [%s])"), argv);
			return false;
		}
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_LevelOpen);
	}
};
class BCC_RecompileShader :public BearEngine::BearConsoleCommand
{
public:
	BCC_RecompileShader() :BearConsoleCommand(TEXT("shader_recompile"), TEXT("recompile shader"), true, true) {}
	~BCC_RecompileShader() {}
	virtual bool Execute(const bchar*argv)
	{
		BearEngine::GResourceManager->RecompileShaders();
		return true;
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_RecompileShader);
	}
};
class BCC_ReloadTexture :public BearEngine::BearConsoleCommand
{
public:
	BCC_ReloadTexture() :BearConsoleCommand(TEXT("texture_reload"), TEXT("reload texture"), true, true) {}
	~BCC_ReloadTexture() {}
	virtual bool Execute(const bchar*argv)
	{
		BearEngine::GResourceManager->ReloadTextures();
		return true;
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_ReloadTexture);
	}
};
#define REGSITER(NAME)BearEngine::GConsole->PushCommand(BearCore::bear_new<##NAME>());
void RegisterConsoleCommand()
{
	REGSITER(BCC_Version);
	REGSITER(BCC_VideoMode);
	REGSITER(BCC_Quit);
	REGSITER(BCC_LevelOpen);
	REGSITER(BCC_RecompileShader);
	REGSITER(BCC_ReloadTexture);
}

