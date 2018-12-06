#include "BearEngine.hpp"

BearEngine::BearTerrain::BearTerrain(const BearName & type):BearObject(type,BO_OnlyOne),m_shader(NDefault, NTerrain), m_is_load(false)
{
	VertexBuffer.Create(0,BearVertex::Size() * 4,false);
	int32 index[] =
	{
		2,1,0,1,3,0
	};
	IndexBuffer.Create(index, sizeof(uint32) * 6, false);
	
	BearGraphics::BearShaderConstantsInitializer initializer;

	initializer.Constants.push_back(BearGraphics::CF_R32G32_FLOAT);
	initializer.Constants.push_back(BearGraphics::CF_R32G32_FLOAT);
	initializer.Constants.push_back(BearGraphics::CF_R32G32_FLOAT);

	m_texturem_multiplier = BearGraphics::BearShaderConstantsRef(initializer);

}

BearEngine::BearTerrain::~BearTerrain()
{

}

void BearEngine::BearTerrain::Load(const BearName & name, bsize width, bsize height, const BearName&texture1, const BearName&texture2, const BearName&texture3)
{
	if (name == NNone) {
		m_is_load = false; return;
	}

	m_is_load = true;

	struct
	{
		BearCore::BearVector2<float> Texture1;
		BearCore::BearVector2<float> Texture2;
		BearCore::BearVector2<float> Texture3;
	} multiplier;

	m_sampler.SetTexture(name);
	m_sampler.SetFilter(BearSampler::SF_MAG_MIP_LINEAR);

	BearVertex vectexs[4];
	vectexs[0].Position.set(0, static_cast<float>(height));
	vectexs[1].Position.set(static_cast<float>(width), 0);
	vectexs[2].Position.set(0, 0);
	vectexs[3].Position.set(static_cast<float>(width), static_cast<float>(height));
	vectexs[0].TextureUV.set(0, 1);
	vectexs[1].TextureUV.set(1, 0);
	vectexs[2].TextureUV.set(0, 0);
	vectexs[3].TextureUV.set(1, 1);
	BearCore::bear_copy(reinterpret_cast<BearVertex*>(VertexBuffer.Lock()), vectexs, 4);
	VertexBuffer.Unlock();

	m_samplers[0].SetTexture(texture1);
	m_samplers[1].SetTexture(texture2);
	m_samplers[2].SetTexture(texture3);


	multiplier.Texture1 = m_samplers[0].GetTexture()->GetSize();
	multiplier.Texture2 = m_samplers[1].GetTexture()->GetSize();
	multiplier.Texture3 = m_samplers[2].GetTexture()->GetSize();

	multiplier.Texture1.x = static_cast<float>(width) / multiplier.Texture1.x;
	multiplier.Texture1.y = static_cast<float>(height) / multiplier.Texture1.y;

	multiplier.Texture2.x = static_cast<float>(width) / multiplier.Texture2.x;
	multiplier.Texture2.y = static_cast<float>(height) / multiplier.Texture2.y;

	multiplier.Texture3.x = static_cast<float>(width) / multiplier.Texture3.x;
	multiplier.Texture3.y = static_cast<float>(height) / multiplier.Texture3.y;

	BearCore::bear_copy(m_texturem_multiplier.Lock(), &multiplier, sizeof(multiplier));
	m_texturem_multiplier.Unlock();

}

void BearEngine::BearTerrain::Destroy()
{
	BEAR_OBJECT_DESTROY(BearTerrain);
}

void BearEngine::BearTerrain::Update(float time)
{
	if (!m_is_load)return;
	GRender->SetShader(m_shader);
	GRender->SetPixel(0,m_sampler);
	GRender->SetPixel(1, m_samplers[0]);
	GRender->SetPixel(2, m_samplers[1]);
	GRender->SetPixel(3, m_samplers[2]);
	BearGraphics::BearRenderInterface::SetPixelShaderConstants(0, m_texturem_multiplier);
	GRender->SetVertex(0,BearRender::TM_View);
	BearGraphics::BearRenderInterface::SetVertexBuffer(VertexBuffer);
	BearGraphics::BearRenderInterface::SetIndexBuffer(IndexBuffer);
	BearGraphics::BearRenderInterface::Draw(6);
}

void BearEngine::BearTerrain::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearTerrain::Load(const BearCore::BearInputStream * stream)
{
}
