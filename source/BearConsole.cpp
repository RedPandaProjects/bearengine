#include "BearEngine.hpp"
BearEngine::BearConsole * BearEngine::GConsole=0;
BearEngine::BearConsole::BearConsole(const BearName & type):BearObject(type,BO_ForGame| BO_OnlyOne), Show(0)
{
	m_text = GObjectManager->Create<BearRenderText>(TEXT("BearEngine::BearRenderText"));
	m_text->SetFont(NDefault);
	m_text->Text = TEXT("test");
	m_text->SetMatrix(BearRender::TM_Othro);

	m_box = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_box->SetMatrix(BearRender::TM_Othro);
	m_list_box = GObjectManager->Create<BearSprite>(TEXT("BearEngine::BearSprite"));
	m_list_box->SetMatrix(BearRender::TM_Othro);
	m_box->SetTexutre(TEXT("ui_console"));
}

BearEngine::BearConsole::~BearConsole()
{
	m_text->Destroy();
	m_box->Destroy();
	m_list_box->Destroy();


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
		Show = !Show;

	if (Show)
	{
		auto ScreenSize = GGeneralViewport->GetSizeFloat();
		m_box->Size.x = ScreenSize.x;
		m_box->Size.y = (float)m_text->GetSizeFont() * 10;
		BEAR_ASSERT(ScreenSize.y> m_text->GetSizeFont()+m_box->Size.y);
		m_text->MaxWidth = m_box->Size.x;
		m_box->Update(time);
		m_text->Update(time);

	}
}
