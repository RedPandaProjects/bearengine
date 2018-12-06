#include "BearEngine.hpp"
#define REGISTER_KEY_NAME(name) BEARENGINE_API  BearEngine::BearName BearEngine::Key##name;
#include "BearIO/BearInputNames.h"
BEARENGINE_API  BearEngine::BearInput*BearEngine::GInput=0;
BearEngine::BearInput::BearInput(const BearName & type):BearObject(type,BO_OnlyOne), m_mouse_scroll(0)
{
#define REGISTER_KEY_NAME(name)  Key##name=TEXT(BEAR_TO_STRING(name));\
m_keys.insert(Key##name,KS_None);
#include "BearIO/BearInputNames.h"
#ifdef WINDOWS
	m_keys_windows.insert( 'A' , KeyA);
	m_keys_windows.insert( 'B', KeyB);
	m_keys_windows.insert( 'C', KeyC);
	m_keys_windows.insert( 'D', KeyD);
	m_keys_windows.insert( 'E', KeyE);
	m_keys_windows.insert( 'F', KeyF);
	m_keys_windows.insert( 'G', KeyG);
	m_keys_windows.insert( 'H', KeyH);
	m_keys_windows.insert( 'I', KeyI);
	m_keys_windows.insert( 'J', KeyJ);
	m_keys_windows.insert( 'K', KeyK);
	m_keys_windows.insert( 'L', KeyL);
	m_keys_windows.insert( 'M', KeyM);
	m_keys_windows.insert( 'N', KeyN);
	m_keys_windows.insert( 'O', KeyO);
	m_keys_windows.insert( 'P', KeyP);
	m_keys_windows.insert( 'Q', KeyQ);
	m_keys_windows.insert( 'R', KeyR);
	m_keys_windows.insert( 'S', KeyS);
	m_keys_windows.insert( 'T', KeyT);
	m_keys_windows.insert( 'U', KeyU);
	m_keys_windows.insert( 'V', KeyV);
	m_keys_windows.insert( 'W', KeyW);
	m_keys_windows.insert( 'X', KeyX);
	m_keys_windows.insert( 'Y', KeyY);
	m_keys_windows.insert( 'Z', KeyZ);
	m_keys_windows.insert( '0', KeyNum0);
	m_keys_windows.insert( '1', KeyNum1);
	m_keys_windows.insert( '2', KeyNum2);
	m_keys_windows.insert( '3', KeyNum3);
	m_keys_windows.insert( '4', KeyNum4);
	m_keys_windows.insert( '5', KeyNum5);
	m_keys_windows.insert( '6', KeyNum6);
	m_keys_windows.insert( '7', KeyNum7);
	m_keys_windows.insert( '8', KeyNum8);
	m_keys_windows.insert( '9', KeyNum9);
	m_keys_windows.insert( VK_ESCAPE, KeyEscape);
	m_keys_windows.insert( VK_LCONTROL, KeyLControl);
	m_keys_windows.insert( VK_LSHIFT, KeyLShift);
	m_keys_windows.insert( VK_LMENU, KeyLAlt);
	m_keys_windows.insert( VK_LWIN, KeyLSystem);
	m_keys_windows.insert( VK_RCONTROL, KeyRControl);
	m_keys_windows.insert( VK_RSHIFT, KeyRShift);
	m_keys_windows.insert( VK_RMENU, KeyRAlt);
	m_keys_windows.insert( VK_RWIN, KeyRSystem);
	m_keys_windows.insert( VK_APPS, KeyMenu);
	m_keys_windows.insert( VK_OEM_4, KeyLBracket);
	m_keys_windows.insert( VK_OEM_6, KeyRBracket);
	m_keys_windows.insert( VK_OEM_1, KeySemiColon);
	m_keys_windows.insert( VK_OEM_COMMA, KeyComma);
	m_keys_windows.insert( VK_OEM_PERIOD, KeyPeriod);
	m_keys_windows.insert( VK_OEM_7, KeyQuote);
	m_keys_windows.insert( VK_OEM_2, KeySlash);
	m_keys_windows.insert( VK_OEM_5, KeyBackSlash);
	m_keys_windows.insert( VK_OEM_3, KeyTilde);
	m_keys_windows.insert( VK_OEM_PLUS, KeyEqual);
	m_keys_windows.insert( VK_OEM_MINUS, KeyDash);
	m_keys_windows.insert( VK_SPACE, KeySpace);
	m_keys_windows.insert( VK_RETURN, KeyReturn);
	m_keys_windows.insert( VK_BACK, KeyBackSpace);
	m_keys_windows.insert( VK_TAB, KeyTab);
	m_keys_windows.insert( VK_PRIOR, KeyPageUp);
	m_keys_windows.insert( VK_NEXT, KeyPageDown);
	m_keys_windows.insert( VK_END, KeyEnd);
	m_keys_windows.insert( VK_HOME, KeyHome);
	m_keys_windows.insert( VK_INSERT, KeyInsert);
	m_keys_windows.insert( VK_DELETE, KeyDelete);
	m_keys_windows.insert( VK_ADD, KeyAdd);
	m_keys_windows.insert( VK_SUBTRACT, KeySubtract);
	m_keys_windows.insert( VK_MULTIPLY, KeyMultiply);
	m_keys_windows.insert( VK_DIVIDE, KeyDivide);
	m_keys_windows.insert( VK_LEFT, KeyLeft);
	m_keys_windows.insert( VK_RIGHT, KeyRight);
	m_keys_windows.insert( VK_UP, KeyUp);
	m_keys_windows.insert( VK_DOWN, KeyDown);
	m_keys_windows.insert( VK_NUMPAD0, KeyNumpad0);
	m_keys_windows.insert( VK_NUMPAD1, KeyNumpad1);
	m_keys_windows.insert( VK_NUMPAD2, KeyNumpad2);
	m_keys_windows.insert( VK_NUMPAD3, KeyNumpad3);
	m_keys_windows.insert( VK_NUMPAD4, KeyNumpad4);
	m_keys_windows.insert( VK_NUMPAD5, KeyNumpad5);
	m_keys_windows.insert( VK_NUMPAD6, KeyNumpad6);
	m_keys_windows.insert( VK_NUMPAD7, KeyNumpad7);
	m_keys_windows.insert( VK_NUMPAD8, KeyNumpad8);
	m_keys_windows.insert( VK_NUMPAD9, KeyNumpad9);
	m_keys_windows.insert( VK_F1, KeyF1);
	m_keys_windows.insert( VK_F2, KeyF2);
	m_keys_windows.insert( VK_F3, KeyF3);
	m_keys_windows.insert( VK_F4, KeyF4);
	m_keys_windows.insert( VK_F5, KeyF5);
	m_keys_windows.insert( VK_F6, KeyF6);
	m_keys_windows.insert( VK_F7, KeyF7);
	m_keys_windows.insert( VK_F8, KeyF8);
	m_keys_windows.insert( VK_F9, KeyF9);
	m_keys_windows.insert( VK_F10, KeyF10);
	m_keys_windows.insert( VK_F11, KeyF11);
	m_keys_windows.insert( VK_F12, KeyF12);
	m_keys_windows.insert( VK_PAUSE, KeyPause);
	m_keys_windows.insert( VK_LBUTTON, KeyMouseLeft);
	m_keys_windows.insert( VK_RBUTTON, KeyMouseRight);
	m_keys_windows.insert(VK_MBUTTON, KeyMouseMiddle);
#endif
}

BearEngine::BearInput::~BearInput()
{
}

bool BearEngine::BearInput::IsKeyPress(const BearName & Key)
{
	auto item=m_keys.find(Key);
	if (item != m_keys.end())
		return item->second == KS_Press|| item->second == KS_Down;
	return false;
}

bool BearEngine::BearInput::IsKeyDown(const BearName & Key)
{
	auto item = m_keys.find(Key);
	if (item != m_keys.end())
		return item->second == KS_Down;
	return false;
}

bool BearEngine::BearInput::IsKeyUp(const BearName & Key)
{
	auto item = m_keys.find(Key);
	if (item != m_keys.end())
		return item->second == KS_Up;
	return false;
}

BearCore::BearFVector2 BearEngine::BearInput::GetMousePosition()
{
	POINT P;
	GetCursorPos(&P);
	ScreenToClient(GGeneralViewport->GetWindowHandle(), &P);
	return BearCore::BearFVector2(static_cast<float>(P.x), static_cast<float>(P.y));
}

void BearEngine::BearInput::SetMousePosition(const BearCore::BearFVector2 & position)
{
	POINT point = { static_cast<LONG>(position.x),  static_cast<LONG>(position.y) };
	ClientToScreen(GGeneralViewport->GetWindowHandle(), &point);
	SetCursorPos(point.x, point.y);
}

void BearEngine::BearInput::Destroy()
{
	BEAR_OBJECT_DESTROY(BearInput);
}

void BearEngine::BearInput::Update(float time)
{
}

void BearEngine::BearInput::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearInput::Load(const BearCore::BearInputStream * stream)
{
}
