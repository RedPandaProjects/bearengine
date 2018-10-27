#include "BearEngine.hpp"

BearEngine::BearMaterialSprite::BearMaterialSprite():BearMaterial(BearResourcesController::GetPixelShader(TEXT("default")), BearResourcesController::GetVertexShader(TEXT("sprite")))
{
	
}

BearEngine::BearMaterialSprite::~BearMaterialSprite()
{	
	clear();
}

void BearEngine::BearMaterialSprite::setTexture1(BearTexture2DResource & texture)
{
	BearResourcesController::FreeTexture2D(m_texture);
	m_texture = texture;
}

void BearEngine::BearMaterialSprite::setMatrix(BearCore::BearMatrix & matrix)
{
	m_matrix = matrix;
}

void BearEngine::BearMaterialSprite::setRGBA1(float R, float G, float B, float A)
{
	m_texture_uv = BearCore::BearVector4<float>(R, G, B, A);
}

void BearEngine::BearMaterialSprite::set()
{
	BearMaterial::set();
	BearRender::SetTexture2D("textuer", m_texture);
	BearGraphics::BearRenderInterface::SetItemInVertexShader("matrix", m_matrix);
	BearGraphics::BearRenderInterface::SetItemInVertexShader("textureUV",m_texture_uv.x,m_texture_uv.y,m_texture_uv.x1,m_texture_uv.y1);
}

void BearEngine::BearMaterialSprite::clear()
{
	BearResourcesController::FreeTexture2D(m_texture);
	BearMaterial::clear();
}
