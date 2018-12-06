#include "BearEngine.hpp"

BearEngine::BearRenderText::BearRenderText(const BearName & type):BearObject(type,0),m_font(0),m_shader(NDefault,NFont), MaxWidth(FLT_MAX), m_type_matrix(BearRender::TM_View)
{
	m_sampler.SetFilter(BearSampler::SF_MAG_MIP_POINT);
	m_shader.SetBlend(BearShader::BF_SRC_ALPHA, BearShader::BF_INV_SRC_ALPHA);
}

BearEngine::BearRenderText::~BearRenderText()
{
	if (m_font)GResourceManager->Destroy(m_font);
}

void BearEngine::BearRenderText::SetFont(const BearName& name)
{
	if (m_font)GResourceManager->Destroy(m_font);
	m_font = GResourceManager->GetFont(name);
	m_sampler.SetTexture(m_font->get()->GetTextureName());
}

void BearEngine::BearRenderText::Destroy()
{
	BEAR_OBJECT_DESTROY(BearRenderText);
}

void BearEngine::BearRenderText::Update(float time)
{
	bsize size = Text.size();
	if (m_font == 0|| !size)return;
	auto font = m_font->get();
	auto pos = Position;
	BearCore::BearVector4<float> TextureUV;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(Text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font->CharsInfo.find(ch_);
			pos.x += item->second.advance;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font->CharsInfo.find(ch_);
			pos.x += item->second.advance * 4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y += font->GetSize();
			pos.x = Position.x;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font->CharsInfo.find(ch_);
			if (item != font->CharsInfo.end())
			{
				GRender->SetShader(m_shader);
				GRender->SetPixel(0, m_sampler);

				TextureUV = item->second.textureUV;
				if (pos.x + item->second.advance > MaxWidth)
				{
					pos.y += font->GetSize();
					pos.x = Position.x;
				}

				{
					float x = pos.x + item->second.position.x, y = pos.y + item->second.position.y;
					float width = item->second.size.x;
					float height = item->second.size.y;
					GRender->SetShader(m_shader);
					GRender->SetPixel(0, m_sampler);
					m_vectex[0].Position.set(x, y + height);
					m_vectex[1].Position.set(x + width, y);
					m_vectex[2].Position.set(x, y);
					m_vectex[3].Position.set(x + width, y + height);
					m_vectex[0].TextureUV.set(TextureUV.x, TextureUV.y1);
					m_vectex[1].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y + TextureUV.y);
					m_vectex[2].TextureUV.set(TextureUV.x, TextureUV.y);
					m_vectex[3].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y1 + TextureUV.y);
					GRender->SetVertex(0,m_type_matrix);
					G2DPlane->Update(m_vectex);
				}
					pos.x += item->second.advance;
			

				//m_matrix = m_matrix * GRender->GetOthro();

			/*	BearGraphics::BearRenderInterface::SetItemToVertexShader("matrix", m_matrix);
				BearGraphics::BearRenderInterface::SetItemToVertexShader("uv", TextureUV);*/
			//	G2DPlane->Update(time);
			}
		}

	}
}

void BearEngine::BearRenderText::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearRenderText::Load(const BearCore::BearInputStream * stream)
{
}
