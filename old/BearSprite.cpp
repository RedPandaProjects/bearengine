#include "BearEngine.hpp"
extern  BearEngine::BearMeshObject Rect2DMesh;
extern   BearCore::BearMatrix Othro;;
BearEngine::BearSprite::BearSprite() :m_position(0, 0), m_size(1, 1),m_rotation(0), m_material(0), m_texture_uv(0,0,1,1)
{

}

BearEngine::BearSprite::~BearSprite()
{
	clear();
}

void BearEngine::BearSprite::clear()
{
	if(m_material)
	m_material->clear();
	BearCore::bear_delete((BearMaterialDefault*)m_material);
}

void BearEngine::BearSprite::updateMatrix()
{
	if (!m_material)
	{
		m_material = BearCore::bear_new<BearMaterialSprite>();
	}

	BearCore::BearMatrix Object;
	Object.buildIdentity();

	Object = Object * BearCore::BearMatrix().scale(m_size.x, m_size.y, 0);
	Object = Object * BearCore::BearMatrix().rotateZ(m_rotation);
	Object = Object * BearCore::BearMatrix().translation(m_position.x, m_position.y, 0);
	m_material->setMatrix(Object * Othro);

	m_material->setRGBA1(m_texture_uv.x, m_texture_uv.y, m_texture_uv.x1, m_texture_uv.y1);
}

void BearEngine::BearSprite::setTexture(const bchar * texture, bool alpha )
{
	if (alpha)
	{
		clear();
		m_material = BearCore::bear_new<BearMaterialSpriteWithAlpha>();
	}
	updateMatrix();
	m_material->setTexture1(BearResourcesController::GetTexture2D(texture));
}

void BearEngine::BearSprite::draw()
{
	
	BearRender::DrawMeshObject(Rect2DMesh,m_material);
}
