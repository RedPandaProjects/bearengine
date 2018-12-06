#include "BearEngine.hpp"

BearEngine::BearTile::BearTile(const BearName & type) :BearObject(type, 0), m_sampler(NNull), m_shader(NDefault, NDefault), TextureUV(0, 0, 1, 1), Rect(0, 0, 1, 1)
{
	m_sampler.SetFilter(BearSampler::SF_MAG_MIP_POINT);
	m_sampler.SetMode(BearSampler::SM_CLAMP);
}

BearEngine::BearTile::~BearTile()
{
}

void BearEngine::BearTile::SetTexutre(const BearName & name)
{
	m_sampler.SetTexture(name);
}

void BearEngine::BearTile::Destroy()
{
	BEAR_OBJECT_DESTROY(BearTile)
}

void BearEngine::BearTile::Update(float time)
{
	GRender->SetShader(m_shader);
	GRender->SetPixel(0, m_sampler);
	m_vectex[0].Position.set(Position.x, Position.y + Size.y);
	m_vectex[1].Position.set(Position.x+ Size.x, Position.y);
	m_vectex[2].Position.set(Position.x, Position.y);
	m_vectex[3].Position.set(Position.x + Size.x, Position.y + Size.y);
	m_vectex[0].TextureUV.set(TextureUV.x, TextureUV.y1);
	m_vectex[1].TextureUV.set(TextureUV.x1+ TextureUV.x, TextureUV.y+ TextureUV.y);
	m_vectex[2].TextureUV.set(TextureUV.x, TextureUV.y);
	m_vectex[3].TextureUV.set(TextureUV.x1+ TextureUV.x, TextureUV.y1+ TextureUV.y);
	GRender->SetVertex(0,BearRender::TM_View);
	G2DPlane->Update(m_vectex);
}

void BearEngine::BearTile::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearTile::Load(const BearCore::BearInputStream * stream)
{
}
