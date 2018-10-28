#include "BearEngine.hpp"
extern  BearEngine::BearMeshObject *Rect2DMesh;
extern   BearCore::BearMatrix Othro;;



BearEngine::BearSprite * BearEngine::BearSprite::Create(const bchar * texture, bool alpha)
{
	auto type = BearCore::bear_alloc< BearSprite>(1);
	return new(type)BearSprite(texture, alpha);

}

void BearEngine::BearSprite::destroy()
{
	m_material->destroy();
	this->~BearSprite();
	BearCore::bear_free(this);
}

BearEngine::BearSprite::~BearSprite()
{

}

void BearEngine::BearSprite::draw()
{
	if (m_update)update();
	BearRender::DrawMeshObject(Rect2DMesh, m_material);
}

BearEngine::BearSprite::BearSprite(const bchar * texture, bool alpha) :m_update(false),m_position(0, 0), m_size(1, 1), m_rotation(0), m_material(0), m_texture_uv(0, 0, 1, 1)
{
	if (alpha)
	{
		BearMaterialSpriteAlpha* mat = BearMaterialSpriteAlpha::Create();
		mat->Texture = BearTexture2D::Create(texture);
		mat->Matrix.buildIdentity();
		mat->TextureUV.set(0, 0, 1, 1);
		m_material = mat;
	}
	else
	{
		BearMaterialSprite* mat = BearMaterialSprite::Create();
		mat->Texture = BearTexture2D::Create(texture);
		mat->Matrix.buildIdentity();
		mat->TextureUV.set(0, 0, 1, 1);
		m_material = mat;
	}
}

void BearEngine::BearSprite::update()
{
	m_update = false;
	BearCore::BearMatrix Object;
	Object.buildIdentity();

	Object = Object * BearCore::BearMatrix().scale(m_size.x, m_size.y, 0);
	Object = Object * BearCore::BearMatrix().rotateZ(m_rotation);
	Object = Object * BearCore::BearMatrix().translation(m_position.x, m_position.y, 0);

	m_material->Matrix = Object * Othro;
	if (m_material->suportAlpha())
	{
		BearMaterialSpriteAlpha* mat = dynamic_cast<BearMaterialSpriteAlpha*>(m_material);
		mat->TextureUV = m_texture_uv;
	}
	else
	{
		BearMaterialSprite* mat = dynamic_cast<BearMaterialSprite*>(m_material);
		mat->TextureUV = m_texture_uv;
	}
}
