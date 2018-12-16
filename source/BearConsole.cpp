#include "BearEngine.hpp"
BearEngine::BearConsole * BearEngine::GConsole=0;

BearEngine::BearConsole::BearConsole(const BearName & type):BearObject(type,BO_ForGame| BO_OnlyOne), Show(0), m_timer_cursor(0)
{
	m_text = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_text->SetFont(NDefault);
	m_text->SetMatrix(BearRender::TM_Othro);

	m_text_in = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_text_in->SetFont(NDefault);
	m_text_in->SetMatrix(BearRender::TM_Othro);

	m_box = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_box->SetMatrix(BearRender::TM_Othro);
	m_list_box = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_list_box->SetMatrix(BearRender::TM_Othro);
	m_box->SetTexutre(TEXT("ui_console"));
	
}

BearEngine::BearConsole::~BearConsole()
{
	m_text->Destroy();
	m_text_in->Destroy();
	m_box->Destroy();
	m_list_box->Destroy();
	auto begin = m_commands.begin();
	auto end = m_commands.end();
	while (begin != end)
	{
		(*begin)->Destroy();
		begin++;
	}
}

void BearEngine::BearConsole::CallStack()
{
	auto begin = m_command_stack.begin();
	auto end = m_command_stack.end();
	while (begin != end)
	{
		ExecuteImpl(**begin);
		begin++;
	}
	m_command_stack.clear_not_free();
}

void BearEngine::BearConsole::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearConsole::Load(const BearCore::BearInputStream * stream)
{
}

void BearEngine::BearConsole::Destroy()
{
	BEAR_OBJECT_DESTROY(BearConsole);
}

void BearEngine::BearConsole::Update(float time)
{
	if (GInput->IsKeyDown(KeyTilde))
	{
		Show = !Show;
	}
	else if (Show)
	{
		if (GInput->GetInputString().size())
		{
			m_command.append(GInput->GetInputString());
			for (bsize i = 0; i < m_command.size(); i++)
			{
				if (m_command[i] == TEXT('\b'))
				{
					m_command.erase(i);
					if(i)	m_command.erase(i-1);
					i = 0;
				}
			}
		}
		if(GInput->IsKeyDown(KeyReturn))
		{
			Execute(*m_command);
			m_command.clear();
		}
		m_timer_cursor += time;
		m_text->Text.clear();
		auto ScreenSize = GRender->GetSizeFloat();

		m_box->Size.x = ScreenSize.x;
		m_box->Size.y = (float)m_text->GetSizeFont() * 11 + (float)m_text->GetSizeFont()/3;


		m_text->Position.y = (float)m_text->GetSizeFont() / 6.f;
		m_text_in->Position.y= (float)m_text->GetSizeFont() * 10 + (float)m_text->GetSizeFont() / 6;

		m_text_in->Text.clear_no_free();
		m_text_in->Text.append(TEXT(">")).append( m_command);

		if (m_timer_cursor >= 1.f) 
		{
			m_timer_cursor = 0;
		}
		else if (m_timer_cursor >= 0.5f)
		{
			m_text_in->Text.append(TEXT("_"));
		}

		BEAR_ASSERT(ScreenSize.y> m_text->GetSizeFont()+m_box->Size.y);

		m_text->MaxWidth = m_box->Size.x;
		m_box->Update(time);

		auto &logList = BearCore::BearLog::Lock();

		auto begin = logList.begin();
		auto end = logList.end();


		if (logList.size() >= 10)begin = end - 10;

		bsize max_size_string =static_cast<bsize>( m_text->MaxWidth) / m_text->GetSizeFont();

		for (bsize i=0;i< 10&&begin !=end;i++)
		{
		
			m_text->Text.append(**begin).append(TEXT("\n"));
			i += begin->size() / max_size_string;
			begin++;
		}

		BearCore::BearLog::Unlock();

		m_text->Update(time);
		m_text_in->Update(time);

	}
}

bool BearEngine::BearConsole::Execute(const bchar * command_)
{
	BearCore::BearString name, command(command_);
	command.sub_space_in_begin();
	command.read_to(TEXT(' '), name);
	name.sub_space_in_end();

	command.sub_space_in_begin();
	command.sub_space_in_end();

	auto item = BearCore::bear_lower_bound(m_commands.begin(), m_commands.end(), name, [](auto a, const BearCore::BearString&name)->bool {return a->GetName() < name; });
	{
		if (item != m_commands.end() && (*item)->GetName() == name)
		{
			if (!(*item)->IsEmpyArgs() && !command.size())
			{
				(*item)->Status();	
				return false;
			}
			else
			{
				if ((*item)->IsCallOnlyAtBegin())
				{
					m_command_stack.push_back(command_); return true;
				}
				else
				{
					return(*item)->Execute(*command);
				}
			}
		}
		else
		{
			BearCore::BearLog::Printf(TEXT("# error, command[%s] not found!"), *name);
		}
	}


	return false;
}

void BearEngine::BearConsole::PushCommand(BearConsoleCommand * command)
{
	auto item = BearCore::bear_lower_bound(m_commands.begin(), m_commands.end(), command, [](auto a, BearConsoleCommand * b)->bool {return (*a) < (*b); });
	if(item!= m_commands.end())
	BEAR_ASSERT(!(*command == **item));
	m_commands.insert(item, command);
}

bool BearEngine::BearConsole::ExecuteImpl(const bchar * command_)
{
	BearCore::BearString name,command(command_);
	command.sub_space_in_begin();
	command.read_to(TEXT(' '), name);
	name.sub_space_in_end();

	command.sub_space_in_begin();
	command.sub_space_in_end();

	auto item = BearCore::bear_lower_bound(m_commands.begin(), m_commands.end(), name, [](auto a, const BearCore::BearString&name)->bool {return a->GetName() < name; });
	{
		if (item != m_commands.end() && (*item)->GetName() == name)
		{
			if (!(*item)->IsEmpyArgs() && !command.size())
			{
				(*item)->Status();	return false;
			}
			else
			{
				return(*item)->Execute(*command);	 
			}
		}
		else
		{
			BearCore::BearLog::Printf(TEXT("# error, command[%s] not found!"), *name);
		}
	}


	return false;
}
