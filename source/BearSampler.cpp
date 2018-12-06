#include "BearEngine.hpp"

BearEngine::BearSampler::BearSampler():m_texture(0), m_mode(SM_WRAP), m_filter(SF_MAG_MIP_POINT)
{
}

BearEngine::BearSampler::BearSampler(const BearName & texture) : m_texture(0), m_mode(SM_WRAP), m_filter(SF_MAG_MIP_POINT)
{
	if(texture!=NNull)
	m_texture = GResourceManager->GetTexture2D(texture);
}

BearEngine::BearSampler::~BearSampler()
{
	if (m_texture)GResourceManager->Destroy(m_texture);
}

void BearEngine::BearSampler::swap(BearSampler & right)
{
	BearCore::bear_swap(m_texture, right.m_texture);
	BearCore::bear_swap(m_filter, right.m_filter);
	BearCore::bear_swap(m_mode, right.m_mode);
}

BearEngine::BearSampler::BearSampler(BearSampler & right) :m_texture(0), m_mode(SM_WRAP), m_filter(SF_MAG_MIP_POINT)
{
	swap(right);
}

BearEngine::BearSampler & BearEngine::BearSampler::operator=(BearSampler & right)
{
	swap(right);
	return *this;
}

void BearEngine::BearSampler::SetTexture(const BearName & texture)
{
	if (m_texture)GResourceManager->Destroy(m_texture);
	m_texture = GResourceManager->GetTexture2D(texture);
}
