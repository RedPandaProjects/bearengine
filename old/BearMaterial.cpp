#include "BearEngine.hpp"

 BearEngine::BearMaterial::BearMaterial(BearPixelShaderResource pixel, BearVertexShaderResource vertex)
{
	m_ps = pixel;
	m_vs = vertex;
}

 void BearEngine::BearMaterial::setRG1(float R, float G)
 {
 }

 void BearEngine::BearMaterial::setRGBA1(float R, float G, float B, float A)
 {
 }

 void BearEngine::BearMaterial::setTexture1(BearTexture2DResource & texture)
{
}

void BearEngine::BearMaterial::setMatrix(BearCore::BearMatrix & matrix)
{
}

void BearEngine::BearMaterial::clear()
{
	BearResourcesController::FreeVertexShader(m_vs);
	BearResourcesController::FreePixelShader(m_ps);
}

BearEngine::BearMaterial::~BearMaterial()
{
	clear();
}

void BearEngine::BearMaterial::set()
{
	BearRender::SetPixelShader(m_ps);
	BearRender::SetVertexShader(m_vs);
}

bool BearEngine::BearMaterial::alpha()
{
	return false;
}
