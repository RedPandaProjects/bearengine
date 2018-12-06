#include "BearEngine.hpp"

 BearCore::BearWindow Window;

 extern bool bEditor;

void BearEngine::BearDevice::Initialize()
{
	if(!bEditor)
	Window.create(TEXT("test"), 1024, 768, false);
	BEAR_ASSERT(BearGraphics::BearRenderInterface::Initialize(TEXT("bear_dx11")));


}

void BearEngine::BearDevice::Destory()
{
	BearGraphics::BearRenderInterface::Destroy();
	Window.close();
}

const bchar * BearEngine::BearDevice::GetNameGraphics()
{
	return TEXT("dx11");
}

bool BearEngine::BearDevice::Update()
{
	return Window.draw(true);
}
