#include "BearEngine.hpp"

BearEngine::BearSprite::BearSprite(const BearName & type) :BearObject(type, 0), m_sampler(NNull), m_shader(NSprite, NDefault), Rotation(0), TextureUV(0, 0, 1, 1), Rect(0, 0, 1, 1),Center(0,0),m_type_matrix(BearRender::TM_View)
{
	m_sampler.SetFilter(BearSampler::SF_MAG_MIP_POINT);
	m_sampler.SetMode(BearSampler::SM_CLAMP);
	m_shader.SetBlend(BearShader::BF_SRC_ALPHA, BearShader::BF_INV_SRC_ALPHA);
}

BearEngine::BearSprite::~BearSprite()
{
}

void BearEngine::BearSprite::SetTexutre(const BearName & name)
{
	m_sampler.SetTexture(name);
}

void BearEngine::BearSprite::Destroy()
{
	BEAR_OBJECT_DESTROY(BearSprite)
}

void BearEngine::BearSprite::Update(float time)
{
	m_matrix.BuildIdentity();
	m_matrix =  BearCore::BearMatrix().Translation(Center.x/ Size.x, Center.y / Size.x, 0);
	m_matrix = m_matrix * BearCore::BearMatrix().RotateZ(Rotation);
	m_matrix = m_matrix * BearCore::BearMatrix().Scale(Size.x, Size.y, 0);
	m_matrix = m_matrix * BearCore::BearMatrix().Translation(Position.x,Position.y,0);


	GRender->SetShader(m_shader);
	GRender->SetPixel(0, m_sampler);
	m_vectex[0].Position.set(0, 1);
	m_vectex[1].Position.set(1, 0);
	m_vectex[2].Position.set(0,0);
	m_vectex[3].Position.set(1, 1);
	m_vectex[0].TextureUV.set(TextureUV.x, TextureUV.y1);
	m_vectex[1].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y + TextureUV.y);
	m_vectex[2].TextureUV.set(TextureUV.x, TextureUV.y);
	m_vectex[3].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y1 + TextureUV.y);
	GRender->SetVertex(0,m_type_matrix);
	GRender->SetVertex(1, m_matrix);
	G2DPlane->Update(m_vectex);
}

void BearEngine::BearSprite::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearSprite::Load(const BearCore::BearInputStream * stream)
{
}
