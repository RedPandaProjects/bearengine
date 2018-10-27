#include "BearEngine.hpp"

 BearCore::BearWindow Window;
 BearCore::BearMatrix Othro;

void BearEngine::BearDevice::Initialize()
{
	Window.create(TEXT("test"), 1024, 768, false);
	BEAR_ASSERT(BearGraphics::BearRenderInterface::Initialize(TEXT("bear_dx11")));
	Othro.buildOrthoOffCenter(1024, 768, FLT_MIN, 100.f);
}

void BearEngine::BearDevice::Destory()
{
	BearGraphics::BearRenderInterface::Destroy();
	Window.close();
}

bool BearEngine::BearDevice::Update()
{
	return Window.draw(true);
}
