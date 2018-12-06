#include "BearEngine.hpp"
BEARENGINE_API BearEngine::Bear2DPlane*BearEngine::G2DPlane;
BearEngine::Bear2DPlane::Bear2DPlane(const BearName & type):BearObject::BearObject(type,BO_OnlyOne)
{

	/*float vertex[] =
	{
		-1.0f, -1.0f, 0.0f,0,0,
		0.0f, 1.0f, 0.0f,0,0,
		1.0f, -1.0f, 0.0f,0,0,
	};*/
	

	/*BearVertex test[3];
	test[0].Position.set(-1, -1,0);
	test[1].Position.set(0, 1,0);
	test[2].Position.set(1, -1,0);
	/*float vertex[] = {
		0.f, 1.0f, 0, 0, 1,
		1.f, 0.0f, 0, 1, 0,
		0.f ,0.0f, 0, 0, 0,
		1.f, 1.0f, 0, 1, 1
	};
	*/
	VertexBuffer.Create(BearVertex::Size()*4);
	int32 index[] =
	{
		2,1,0,1,3,0
	};
	IndexBuffer.Create(index, sizeof(uint32) *  6, false);

}

BearEngine::Bear2DPlane::~Bear2DPlane()
{
}

void BearEngine::Bear2DPlane::Destroy()
{
	BEAR_OBJECT_DESTROY(Bear2DPlane);
}

void BearEngine::Bear2DPlane::Update(BearVertex vectex[4])
{
	BearCore::bear_copy(reinterpret_cast<BearVertex*>(VertexBuffer.Lock()), vectex, 4);
	VertexBuffer.Unlock();
	BearGraphics::BearRenderInterface::SetVertexBuffer(VertexBuffer);
	BearGraphics::BearRenderInterface::SetIndexBuffer(IndexBuffer);
	BearGraphics::BearRenderInterface::Draw(6);
}

void BearEngine::Bear2DPlane::Update(float time)
{
}

void BearEngine::Bear2DPlane::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::Bear2DPlane::Load(const BearCore::BearInputStream * stream)
{
}
