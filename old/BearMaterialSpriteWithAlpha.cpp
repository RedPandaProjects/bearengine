#include "BearEngine.hpp"

BearEngine::BearMaterialSpriteWithAlpha::BearMaterialSpriteWithAlpha() :BearMaterial(BearResourcesController::GetPixelShader(TEXT("alpha")), BearResourcesController::GetVertexShader(TEXT("sprite")))
{

}

BearEngine::BearMaterialSpriteWithAlpha::~BearMaterialSpriteWithAlpha()
{
	clear();
}

void BearEngine::BearMaterialSpriteWithAlpha::setTexture1(BearTexture2DResource & texture)
{
	BearResourcesController::FreeTexture2D(m_texture);
	m_texture = texture;
}

void BearEngine::BearMaterialSpriteWithAlpha::setMatrix(BearCore::BearMatrix & matrix)
{
	m_matrix = matrix;
}

void BearEngine::BearMaterialSpriteWithAlpha::setRGBA1(float R, float G, float B, float A)
{
	m_texture_uv = BearCore::BearVector4<float>(R, G, B, A);
}

void BearEngine::BearMaterialSpriteWithAlpha::set()
{
	BearMaterial::set();
	BearRender::SetTexture2D("textuer", m_texture);
	BearGraphics::BearRenderInterface::SetItemInVertexShader("matrix", m_matrix);
	BearGraphics::BearRenderInterface::SetItemInVertexShader("textureUV", m_texture_uv.x, m_texture_uv.y, m_texture_uv.x1, m_texture_uv.y1);
}

void BearEngine::BearMaterialSpriteWithAlpha::clear()
{
	BearResourcesController::FreeTexture2D(m_texture);
	BearMaterial::clear();
}

bool BearEngine::BearMaterialSpriteWithAlpha::alpha()
{
	return true;
}
