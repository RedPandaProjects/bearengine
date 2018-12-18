#include "BearEngine.hpp"
BearEngine::BearConsole * BearEngine::GConsole=0;

BearEngine::BearConsole::BearConsole(const BearName & type):BearObject(type,BO_ForGame| BO_OnlyOne), Show(0), m_timer_cursor(0), m_shift_item(0),m_id_item(-1)
{
	m_render_command = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_render_command->SetFont(NDefault);
	m_render_command->SetMatrix(BearRender::TM_Othro);

	m_render_finder = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_render_finder->SetFont(NDefault);
	m_render_finder->SetMatrix(BearRender::TM_Othro);

	m_render_log = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_render_log->SetFont(NDefault);
	m_render_log->SetMatrix(BearRender::TM_Othro);

	m_plane_log= GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_plane_log->SetMatrix(BearRender::TM_Othro);
	m_plane_log->SetTexutre(TEXT("ui_console"));

	m_plane_finder = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_plane_finder->SetMatrix(BearRender::TM_Othro);
	m_plane_finder->SetTexutre(TEXT("ui_console"));

	m_plane_item = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_plane_item->SetMatrix(BearRender::TM_Othro);
	m_plane_item->SetTexutre(TEXT("ui_console"));
	m_plane_item->Size.y =static_cast<float>( m_render_finder->GetSizeFont());
	Resize(640, 480);
}

BearEngine::BearConsole::~BearConsole()
{
	m_plane_finder->Destroy();
	m_plane_log->Destroy();
	m_render_command->Destroy();
	m_render_log->Destroy();
	m_render_finder->Destroy();
	m_plane_item->Destroy();
	auto begin = m_command_list.begin();
	auto end = m_command_list.end();
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

void BearEngine::BearConsole::Resize(bsize width, bsize height)
{
	m_render_log->MaxWidth = m_render_command->MaxWidth = static_cast<float>(width);
	bsize count_line = (height/3) / m_render_log->GetSizeFont();
	BEAR_ASSERT(count_line);
	count_line--;
	BEAR_ASSERT(count_line);
	m_plane_log->Size.x = static_cast<float>(width);
	m_plane_log->Size.y = static_cast<float>(count_line+1)*m_render_log->GetSizeFont() + m_render_log->GetSizeFont()/3.f;

	m_render_command->Position.y = m_plane_log->Size.y - m_render_log->GetSizeFont();
	
	
	m_plane_finder->Position.y = m_plane_log->Size.y;
	m_plane_finder->Size.y = m_plane_log->Size.y;

	m_count_line = count_line;
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
		if (GInput->GetInputString().size()&&(GInput->GetInputString()[0] != TEXT('\r') || GInput->GetInputString()[1]))
		{
			m_id_item = -1;
			m_finder_command_data.clear_not_free();
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
			m_finder_command_data.clear_not_free();
			float wigth = 0;
			if (m_command.size())
			{
				auto begin = m_command_list.begin();
				auto end = m_command_list.end();
				while (begin != end)
				{
					if ((*begin)->GetName().exist(*m_command))
					{
						m_shift_item = 0;
						m_finder_command_data.push_back(*(*begin)->GetName());
						wigth = BearCore::bear_max<float>(static_cast<float>(m_render_log->GetSizeLine(*(*begin)->GetName())) + static_cast<float>(m_render_log->GetSizeFont()) / 3.f, wigth);
					}
					begin++;
				}
			}
			m_plane_finder->Size.x = BearCore::bear_max<float>(m_plane_finder->Size.x ,wigth);
			m_plane_finder->Size.y = static_cast<float>(BearCore::bear_min<bsize>(m_count_line, m_finder_command_data.size()))*m_render_log->GetSizeFont() + m_render_log->GetSizeFont() / 3.f;

			
		}
		if(GInput->IsKeyDown(KeyReturn))
		{
			if (m_id_item>=0)
			{
				m_command.assign(m_finder_command_data[m_id_item]).append(TEXT(" "));
				m_finder_command_data.clear_not_free();
				m_id_item = -1;
			}
			else
			{
				m_command_last = m_command;
				Execute(*m_command);
				m_command.clear();
				m_id_item = -1;
			}
		}
		else if(GInput->IsKeyDown(KeyUp)&&m_id_item==-1)
		{
			m_command = m_command_last;
		}
		m_timer_cursor += time;

		m_render_command->Text.clear_no_free();
		m_render_command->Text.append(TEXT(">")).append( m_command);

		if (m_timer_cursor >= 1.f) 
		{
			m_timer_cursor = 0;
		}
		else if (m_timer_cursor >= 0.5f)
		{
			m_render_command->Text.append(TEXT("_"));
		}


		m_plane_log->Update(time);

		auto &logList = BearCore::BearLog::Lock();
		{
			auto begin = logList.begin();
			auto end = logList.end();

			if (logList.size() >= m_count_line)begin = end - m_count_line;

			m_render_log->Position.y = (float)m_render_log->GetSizeFont() / 6.f + m_render_log->GetSizeFont() *BearCore::bear_min<bsize>(m_count_line, logList.size());
			for (bint i = BearCore::bear_max<bint>(m_count_line - logList.size(), 0); i < static_cast<bint>(m_count_line)&&begin != end;)
			{
				end--;
				const bchar*text = **end;
				if (text[0] == TEXT('#') && text[1] == TEXT(' '))
				{
					text += 2;
					m_render_log->Color = BearCore::BearColor::Red;
				}
				else if (text[0] == TEXT('?') && text[1] == TEXT(' '))
				{
					text += 2;
					m_render_log->Color = BearCore::BearColor::Yellow;
				}
				else if (text[0] == TEXT('!') && text[1] == TEXT(' '))
				{
					text += 2;
					m_render_log->Color = BearCore::BearColor::Green;

				}
				else
				{
					m_render_log->Color = BearCore::BearColor::White;
				}
				bsize cln = m_render_log->GetCountLine(text) + 1;
				m_render_log->Position.y -= cln * m_render_log->GetSizeFont();
				i += cln;
				m_render_log->Text.assign(text);
				m_render_log->Update(time);
			}
		}
		BearCore::BearLog::Unlock();
		m_render_command->Update(time);
		if (m_finder_command_data.size())
		{
			bsize count = BearCore::bear_min(m_count_line, m_finder_command_data.size());
			if (GInput->IsKeyDown(KeyDown))
			{
				if (m_id_item == -1) { m_shift_item = 0; m_id_item++; }
				else
				if (m_finder_command_data.size() > static_cast<bsize>(m_id_item)+1)
				{
					m_id_item++;
					if (m_id_item - m_shift_item == count)
					{
						m_id_item = count + m_shift_item;

						m_shift_item++;

					}
				}
			}
			else if (GInput->IsKeyDown(KeyUp))
			{
				if (m_id_item-m_shift_item)
					m_id_item--;
				else if (m_shift_item)
					m_shift_item--;
			}
			m_plane_finder->Update(time);
			auto begin = m_finder_command_data.begin()+m_shift_item;
			auto end = m_finder_command_data.end();

			for (bint i = 0; i < static_cast<bint>(m_count_line) && begin != end; begin++, i++)
			{
				m_render_finder->Text.assign(*begin);
				m_render_finder->Position.y = floorf((float)m_render_log->GetSizeFont() / 6.f + i * m_render_log->GetSizeFont() + m_plane_finder->Position.y);
				m_render_finder->Update(time);
			}

			if (m_id_item >= 0)
			{
				BEAR_ASSERT(m_finder_command_data.size() > static_cast<size_t>(m_id_item));
				m_plane_item->Position.y =  floorf((float)m_render_log->GetSizeFont() / 6.f + static_cast<float>(m_id_item - m_shift_item) * m_render_log->GetSizeFont() + m_plane_finder->Position.y);
				m_plane_item->Size.x = m_plane_finder->Size.x;
				m_plane_item->Update(time);
			}
		}
		
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

	auto item = BearCore::bear_lower_bound(m_command_list.begin(), m_command_list.end(), name, [](auto a, const BearCore::BearString&name)->bool {return a->GetName() < name; });
	{
		if (item != m_command_list.end() && (*item)->GetName() == name)
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
					m_command_stack.push_back(command_);
					return true;
				}
				else
				{
					return(*item)->Execute(*command);
				}
			}
		}
		else
		{
			BearCore::BearLog::Printf(TEXT("# Error, command[%s] not found!"), *name);
		}
	}
	return false;
}

void BearEngine::BearConsole::PushCommand(BearConsoleCommand * command)
{
	auto item = BearCore::bear_lower_bound(m_command_list.begin(), m_command_list.end(), command, [](auto a, BearConsoleCommand * b)->bool {return (*a) < (*b); });
	if(item!= m_command_list.end())
	BEAR_ASSERT(!(*command == **item));
	m_command_list.insert(item, command);
}

bool BearEngine::BearConsole::ExecuteImpl(const bchar * command_)
{
	BearCore::BearString name,command(command_);
	command.sub_space_in_begin();
	command.read_to(TEXT(' '), name);
	name.sub_space_in_end();

	command.sub_space_in_begin();
	command.sub_space_in_end();

	auto item = BearCore::bear_lower_bound(m_command_list.begin(), m_command_list.end(), name, [](auto a, const BearCore::BearString&name)->bool {return a->GetName() < name; });
	{
		if (item != m_command_list.end() && (*item)->GetName() == name)
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
			BearCore::BearLog::Printf(TEXT("# Error, command[%s] not found!"), *name);
		}
	}


	return false;
}
