#include "BearEngine.hpp"

BearEngine::BearShader::BearShader():m_blend(false),m_pixel(0),m_vertex(0)
{
	BearCore::bear_fill(m_vertex_state);
	m_vertex_state[0] = VF_R32G32_FLOAT;
	m_vertex_state[1] = VF_R32G32_FLOAT;
}

BearEngine::BearShader::BearShader(const BearName & vs, const BearName & ps) : m_blend(false)
{
	BearCore::bear_fill(m_vertex_state);
	m_vertex_state[0] = VF_R32G32_FLOAT;
	m_vertex_state[1] = VF_R32G32_FLOAT;
	m_vertex = GResourceManager->GetVertexShader(vs);
	m_pixel = GResourceManager->GetPixelShader(ps);
}

void BearEngine::BearShader::swap(BearShader & right)
{
	BearCore::bear_swap(m_pixel, right.m_pixel);
	BearCore::bear_swap(m_vertex, right.m_vertex);
	BearCore::bear_swap(m_blend, right.m_blend);
	BearCore::bear_swap(m_blend_src, right.m_blend_src);
	BearCore::bear_swap(m_blend_dst, right.m_blend_dst);
}

BearEngine::BearShader::BearShader(BearShader & right) :m_blend(false), m_pixel(0), m_vertex(0)
{
	swap(right);
}

BearEngine::BearShader & BearEngine::BearShader::operator=(BearShader & right)
{
	swap(right);
	return *this;
}

BearEngine::BearShader::~BearShader()
{
	if (!m_vertex)return;
	GResourceManager->Destroy(m_vertex);
	GResourceManager->Destroy(m_pixel);
}
