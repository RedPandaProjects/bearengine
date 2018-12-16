#include "BearEngine.hpp"
BEARENGINE_API extern BearEngine::BearCallBack*BearEngine::GCallBack=0;
BearEngine::BearCallBack::BearCallBack(const BearName&name):BearObject(name,BO_OnlyOne)
{
}

BearEngine::BearCallBack::~BearCallBack()
{
	m_Destroy.call_back();
}

void BearEngine::BearCallBack::Destroy()
{
	BEAR_OBJECT_DESTROY(BearCallBack);
}

void BearEngine::BearCallBack::ObjectsDestroy()
{
	CallBackDestroy();
	m_Destroy.m_list.clear();
	m_Resize.m_list.clear();
	m_Update.m_list.clear();
	m_AppActive.m_list.clear();
	m_AppDeactive.m_list.clear();
}

void BearEngine::BearCallBack::Update(float time)
{
	m_Update.call_back(time);
}

void BearEngine::BearCallBack::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearCallBack::Load(const BearCore::BearInputStream * stream)
{
}
