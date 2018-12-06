#include "BearEngine.hpp"
extern  BearEngine::BearMeshObject *Rect2DMesh;
extern   BearCore::BearMatrix Othro;
BearEngine::BearRenderText * BearEngine::BearRenderText::Create(const bchar * font)
{
	return new(BearCore::bear_alloc<BearRenderText>(1)) BearRenderText(font);
}

void BearEngine::BearRenderText::destroy()
{
	m_font->destroy();
	m_material_font->destroy();
	this->~BearRenderText();
	BearCore::bear_free(this);
}

void BearEngine::BearRenderText::draw()
{
	bsize size = text.size();
	auto pos = position;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16( text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = m_font->CharsInfo.find(ch_);
			pos.x += item->second.advance;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = m_font->CharsInfo.find(ch_);
			pos.x += item->second.advance*4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y += m_font->getSize();
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = m_font->CharsInfo.find(ch_);
			if (item != m_font->CharsInfo.end())
			{

				static_cast<BearMaterialFont*>(m_material_font)->TextureUV = item->second.textureUV;
				BearCore::BearMatrix Object;
				Object.buildIdentity();

				Object = Object * BearCore::BearMatrix().scale(item->second.size.x, item->second.size.y, 0);
				Object = Object * BearCore::BearMatrix().translation(pos.x + item->second.position.x, pos.y + item->second.position.y, 0);

				pos.x += item->second.advance;

				m_material_font->Matrix = Object * Othro;

				BearRender::DrawMeshObject(Rect2DMesh, m_material_font);
			}
		}

	}
}

BearEngine::BearRenderText::BearRenderText(const bchar * font)
{
	m_font = BearFont::Create(font);
	m_material_font = BearMaterialFont::Create();
	static_cast<BearMaterialFont*>(m_material_font)->Texture = m_font->getTexture();

}

BearEngine::BearRenderText::~BearRenderText()
{
}
