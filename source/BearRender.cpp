#include "BearEngine.hpp"
static BearGraphics::BearViewPortRef ViewPort;
extern BearCore::BearWindow Window;
static BearGraphics::BearSamplerStateRef SamplerDefault;
static BearGraphics::BearVertexInputLayoutRef VertexInputLayoutDefault;
static BearGraphics::BearBlendStateRef BlendStateAlpha;
static BearGraphics::BearBlendStateRef BlendState;
static BearGraphics::BearDepthStencilStateRef DepthStencilState;
static BearGraphics::BearDepthStencilViewRef DepthStencilView;
 BearEngine::BearMeshObject* Rect2DMesh;
void BearEngine::BearRender::Initialize()
{
	ViewPort.create(Window, false);
	Rect2DMesh = BearEngine::BearMeshObject::Create();
	Rect2DMesh->getVertexArray().resize(4);
	Rect2DMesh->getVertexArray()[0] = BearVertex(0.f, 1.0f, 0, 0, 1);
	Rect2DMesh->getVertexArray()[1] = BearVertex(1.f, 0.0f, 0, 1, 0);
	Rect2DMesh->getVertexArray()[2] = BearVertex(0.f,0.0f, 0, 0,0);
	Rect2DMesh->getVertexArray()[3] = BearVertex(1.f, 1.0f, 0,1, 1);
	Rect2DMesh->getIndexArray().resize(6);
	Rect2DMesh->getIndexArray()[0] = 2;
	Rect2DMesh->getIndexArray()[1] = 1;
	Rect2DMesh->getIndexArray()[2] = 0;
	Rect2DMesh->getIndexArray()[3] = 1;
	Rect2DMesh->getIndexArray()[4] = 3;
	Rect2DMesh->getIndexArray()[5] = 0;



	BearGraphics::BearRenderInterface::AttachRenderTargetView(0, ViewPort);
	BearGraphics::BearRenderInterface::SetViewport(0, 0, 0, 1024, 768);

	BearGraphics::BearSamplerStateInitializer SamplerDefaultInit(BearGraphics::SAM_WRAP);
	SamplerDefaultInit.Filter = BearGraphics::SF_MAG_MIP_POINT;
	SamplerDefaultInit.MaxAnisotropy = 1;
	SamplerDefault = BearGraphics::BearSamplerStateRef(SamplerDefaultInit);

	BearGraphics::BearVertexInputLayoutInitializer initializer;
	initializer.appendItem(TEXT("POSITION"), BearGraphics::ILE_R32G32B32_FLOAT);
	initializer.appendItem(TEXT("UV"), BearGraphics::ILE_R32G32_FLOAT);

	BearGraphics::BearShaderVertexCompilerRef vertexCompiler;
	BearCore::BearString out;
	BEAR_ASSERT(vertexCompiler.compileFromFile(TEXT("..\\..\\content\\stalker2d\\shaders\\dx11\\default.vs"), BearCore::BearEncoding::UTF8, out));

	VertexInputLayoutDefault= BearGraphics::BearVertexInputLayoutRef(initializer, vertexCompiler.begin(), vertexCompiler.getSize());
	BearGraphics::BearRenderInterface::SetVertexInputLayout(VertexInputLayoutDefault);

	BearGraphics::BearDepthStencilStateInitializer DepthStencil;
	DepthStencil.DepthEnable = false;
	DepthStencil.DepthTest = BearGraphics::BearCompareFunction::CF_LESS;
	DepthStencil.StencillEnable = true;
	DepthStencil.StencilReadMask = 0xFF;
	DepthStencil.StencilWriteMask = 0xFF;
	DepthStencil.FrontFace.StencilFailOp = BearGraphics::BearStencilOp::SO_KEEP;
	DepthStencil.FrontFace.StencilDepthFailOp = BearGraphics::BearStencilOp::SO_INCR;
	DepthStencil.FrontFace.StencilPassOp = BearGraphics::BearStencilOp::SO_KEEP;
	DepthStencil.FrontFace.StencilTest = BearGraphics::BearCompareFunction::CF_ALWAYS;
	DepthStencil.BackFace.StencilFailOp = BearGraphics::BearStencilOp::SO_KEEP;
	DepthStencil.BackFace.StencilDepthFailOp = BearGraphics::BearStencilOp::SO_DECR;
	DepthStencil.BackFace.StencilPassOp = BearGraphics::BearStencilOp::SO_KEEP;
	DepthStencil.BackFace.StencilTest = BearGraphics::BearCompareFunction::CF_ALWAYS;


	DepthStencilState = BearGraphics::BearDepthStencilStateRef(DepthStencil);

	BearGraphics::BearBlendStateInitializer blend;
	blend.RenderTarget[0].ColorWriteMask = BearGraphics::BearColorWriteMask::CWM_RGBA;
	blend.RenderTarget[0].Alpha = BearGraphics::BearBlendOp::BO_ADD;
	blend.RenderTarget[0].AlphaDst = BearGraphics::BearBlendFactor::BF_ZERO;
	blend.RenderTarget[0].AlphaSrc = BearGraphics::BearBlendFactor::BF_ONE;
	blend.RenderTarget[0].Color = BearGraphics::BearBlendOp::BO_ADD;
	blend.RenderTarget[0].ColorDst = BearGraphics::BearBlendFactor::BF_INV_SRC_ALPHA;
	blend.RenderTarget[0].ColorSrc = BearGraphics::BearBlendFactor::BF_SRC_ALPHA;
	BlendStateAlpha = BearGraphics::BearBlendStateRef(blend);
	blend.RenderTarget[0].Enable = false;
	BlendState = BearGraphics::BearBlendStateRef(blend);
	BearGraphics::BearRenderInterface::SetBlendState(BlendState, BearCore::BearColor::Transparent);
	DepthStencilView.create(1024, 768, BearGraphics::BearDepthStencilFormat::DSF_DEPTH24_STENCIL8);
	BearGraphics::BearRenderInterface::AttachDepthStencilView(DepthStencilView);
	BearGraphics::BearRenderInterface::SetDepthStencilState(DepthStencilState,0);

}
void BearEngine::BearRender::Clear()
{

	ViewPort.clearColor(BearCore::BearColor::Black);
	DepthStencilView.clearDepth();

}

void BearEngine::BearRender::Swap()
{
	ViewPort.swap();
}

void BearEngine::BearRender::Destory()
{
	ViewPort.close();
	Rect2DMesh->destroy();
	SamplerDefault.clear();
	VertexInputLayoutDefault.clear();
	DepthStencilView.clear();
	DepthStencilState.clear();
	BlendState.clear();
	BlendStateAlpha.clear();
}

void BearEngine::BearRender::AlphaOn()
{
	BearGraphics::BearRenderInterface::SetBlendState(BlendStateAlpha, BearCore::BearColor::Transparent);
}

void BearEngine::BearRender::AlphaOff()
{
	BearGraphics::BearRenderInterface::SetBlendState(BlendState, BearCore::BearColor::Transparent);
}

void BearEngine::BearRender::Set(const BearPixelShader * pixel)
{
	BearGraphics::BearRenderInterface::SetPixelShader(*pixel->get<BearGraphics::BearPixelShaderRef>());
}

void BearEngine::BearRender::Set(const BearVertexShader* vertex)
{
	BearGraphics::BearRenderInterface::SetVertexShader(*vertex->get<BearGraphics::BearVertexShaderRef>());
}

void BearEngine::BearRender::SetPS(const char*name, const BearTexture2D * texture)
{
	BearGraphics::BearRenderInterface::SetItemInPixelShader(name,*texture->get<BearGraphics::BearTexture2DRef>(),SamplerDefault);
}
void BearEngine::BearRender::SetVS(const char*name, const BearTexture2D * texture)
{
	BearGraphics::BearRenderInterface::SetItemInVertexShader(name, *texture->get<BearGraphics::BearTexture2DRef>(), SamplerDefault);
}
void BearEngine::BearRender::DrawMeshObject(BearMeshObject * mesh, BearMaterialInstance * material)
{
	
	BearGraphics::BearRenderInterface::SetIndexBuffer(*mesh->getIndexBuffer()->get<BearGraphics::BearIndexBufferRef>());
	BearGraphics::BearRenderInterface::SetVertexBuffer(*mesh->getVertexBuffer()->get<BearGraphics::BearVertexBufferRef>(),static_cast<uint32>(BearVertex::getSize()));
	material->set();
	if (material->suportAlpha())AlphaOn();
	BearGraphics::BearRenderInterface::Draw(mesh->getSizeIndex());
	if (material->suportAlpha())AlphaOff();
}


