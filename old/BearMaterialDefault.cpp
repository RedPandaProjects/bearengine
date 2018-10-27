#include "BearEngine.hpp"

BearEngine::BearMaterialDefault::BearMaterialDefault():BearMaterial(BearResourcesController::GetPixelShader(TEXT("default")), BearResourcesController::GetVertexShader(TEXT("default")))
{
	
}

BearEngine::BearMaterialDefault::~BearMaterialDefault()
{	
	clear();
}

void BearEngine::BearMaterialDefault::setTexture1(BearTexture2DResource & texture)
{
	BearResourcesController::FreeTexture2D(m_texture);
	m_texture = texture;
}

void BearEngine::BearMaterialDefault::setMatrix(BearCore::BearMatrix & matrix)
{
	m_matrix = matrix;
}

void BearEngine::BearMaterialDefault::set()
{
	BearMaterial::set();
	BearRender::SetTexture2D("textuer", m_texture);
	BearGraphics::BearRenderInterface::SetItemInVertexShader("matrix", m_matrix);
}

void BearEngine::BearMaterialDefault::clear()
{
	BearResourcesController::FreeTexture2D(m_texture);
	BearMaterial::clear();
}
