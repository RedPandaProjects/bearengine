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
	BCC_Version() :BearConsoleCommand(TEXT("version"), TEXT("(no argumet)"),false){}
	~BCC_Version() {}
	virtual bool Execute(const bchar*argv)
	{
		BearCore::BearLog::Printf(TEXT("test"));
		return true;
	}
	virtual void Destroy()
	{
		BEAR_OBJECT_DESTROY(BCC_Version);
	}
};

class BCC_SizeMode :public BearEngine::BearConsoleCommand
{
public:
	BCC_SizeMode() :BearConsoleCommand(TEXT("size_mode"), TEXT("Set size screen [Widht]x[Height]"),true,true) {}
	~BCC_SizeMode() {}
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
		BEAR_OBJECT_DESTROY(BCC_SizeMode);
	}
};

#define REGSITER(NAME)BearEngine::GConsole->PushCommand(BearCore::bear_new<##NAME>());
void RegisterConsoleCommand()
{
	REGSITER(BCC_Version);
	REGSITER(BCC_SizeMode);
}

