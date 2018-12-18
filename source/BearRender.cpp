#include "BearEngine.hpp"
BEARENGINE_API BearEngine::BearRender*BearEngine::GRender=0;

BearEngine::BearRender::BearRender(const BearName&type):BearObject(type,BO_OnlyOne),m_blend_current(0xFFFF), m_vertex_state_current(0xFFFFFFFFFFFFFFFF),GeneralViewport(0)
{
	BEAR_OBJECT_VALUE(Render);
	BearCore::BearLog::Printf(TEXT("Loading render [%s]"), *Render);
	BEAR_FATALERROR(BearGraphics::BearRenderInterface::Initialize(*Render), TEXT("Неудалось загрузить графическию библиотеку [%s]"), *Render);
	BearCore::FS->AppendPath(TEXT("%shaders_cur%"), *Render, TEXT("%shaders%"), 0);
	BearCore::FS->AppendPath(TEXT("%app_shaders_cur%"), *Render, TEXT("%app_shaders%"), 0);
	BearCore::FS->CreatePath(TEXT("%app_shaders_cur%"), 0);



	BearGraphics::BearBlendStateInitializer blend;
	blend.RenderTarget[0].Enable = false;
	m_blend_default = BearGraphics::BearBlendStateRef(blend);

	BearGraphics::BearShaderConstantsInitializer sconst_othro;
	sconst_othro.Constants.push_back(BearGraphics::CF_MATRIX);
	m_sconst_matrix = BearGraphics::BearShaderConstantsRef(sconst_othro, true);
	m_sconst_view = BearGraphics::BearShaderConstantsRef(sconst_othro, true);

	SetView(0, 0, 500, 500);

	BEAR_OBJECT_VALUE_FROM_USER(Width);
	BEAR_OBJECT_VALUE_FROM_USER(Height);
	BEAR_OBJECT_VALUE_FROM_USER(FullScreen);

	/*Resize(Width, Height);
	SetFullScreen(FullScreen);*/
}

BearEngine::BearRender::~BearRender()
{
	if(GeneralViewport)
	GeneralViewport->Destroy();
	m_vertex_state_map.clear();
	m_blend_default.Clear();
	m_sampler_map.clear();
	m_blend_map.clear();
	m_sconst_view.Clear();
	m_sconst_matrix.Clear();
	BearGraphics::BearRenderInterface::Destroy();
}

void BearEngine::BearRender::CreateGeneralViewport()
{	BearGraphics::BearRenderInterface::SetViewport(0, 0, 0, GetSizeFloat().x, GetSizeFloat().y);
	BEAR_OBJECT_VALUE(GeneralViewport);
	BearGraphics::BearRenderInterface::AttachRenderTargetView(0, *GeneralViewport);
	GCallBack->GetResize().add(GeneralViewport, 0);
	GRender->SetView(0, 0, static_cast<float>(Width), static_cast<float>(Height));
	Resize(Width, Height);
	SetFullScreen(FullScreen);
}

void BearEngine::BearRender::Resize(bsize widht, bsize height)
{
	if (widht == GeneralViewport->GetSize().x &&
		height == GeneralViewport->GetSize().y)return ;
	Width = widht;
	Height = height;
	BEAR_OBJECT_VALUE_TO_USER(Width);
	BEAR_OBJECT_VALUE_TO_USER(Height);
	GCallBack->CallBackResize(widht, height);
	BearGraphics::BearRenderInterface::SetViewport(0, 0, 0, GetSizeFloat().x, GetSizeFloat().y);
	BearGraphics::BearRenderInterface::AttachRenderTargetView(0,*GeneralViewport);
}

void BearEngine::BearRender::Resize(float widht, float height)
{
	Resize(static_cast<bsize>(widht), static_cast<bsize>(height));
}

void BearEngine::BearRender::SetFullScreen(bool full_screen)
{

	if (full_screen== GeneralViewport->IsFullScreen())return;
	FullScreen = full_screen;
	BEAR_OBJECT_VALUE_TO_USER(FullScreen);
	GeneralViewport->SetFullScreen(full_screen);
}


void BearEngine::BearRender::Destroy()
{
	BEAR_OBJECT_DESTROY(BearRender);
}

void BearEngine::BearRender::SetShader(BearShader & shader)
{
	BEAR_ASSERT(shader.m_pixel&&shader.m_vertex);


	{
		uint64 id = static_cast<uint64>(shader.m_vertex_state[0])
			| static_cast<uint64>(shader.m_vertex_state[1]) << 4
			| static_cast<uint64>(shader.m_vertex_state[2]) << 8
			| static_cast<uint64>(shader.m_vertex_state[3]) << 12
			| static_cast<uint64>(shader.m_vertex_state[4] << 16
			| static_cast<uint64>(shader.m_vertex_state[5]) << 20)
			| static_cast<uint64>(shader.m_vertex_state[6]) << 24
			| static_cast<uint64>(shader.m_vertex_state[7]) << 28
			| static_cast<uint64>(shader.m_vertex_state[8]) << 32
			| static_cast<uint64>(shader.m_vertex_state[9]) << 36
			| static_cast<uint64>(shader.m_vertex_state[10]) << 40
			| static_cast<uint64>(shader.m_vertex_state[11]) << 44
			| static_cast<uint64>(shader.m_vertex_state[12]) << 48
			| static_cast<uint64>(shader.m_vertex_state[13]) << 52
			| static_cast<uint64>(shader.m_vertex_state[14]) << 56
			| static_cast<uint64>(shader.m_vertex_state[15]) << 60;
		if (m_vertex_state_current != id)
		{
			auto item = m_vertex_state_map.find(id);
			if (item == m_vertex_state_map.end())
			{
				CreateVertexState(shader);
				item = m_vertex_state_map.find(id);
			}
			BearGraphics::BearRenderInterface::SetVertexState(item->second);
			m_vertex_state_current = id;
		}
	}
	BearGraphics::BearRenderInterface::SetPixelShader(shader.m_pixel->get());
	BearGraphics::BearRenderInterface::SetVertexShader(shader.m_vertex->get());
	{
		if (shader.m_blend)
		{
			uint16 id = ((static_cast<uint16>(shader.m_blend_dst) << 8) | (static_cast<uint16>(shader.m_blend_src)));
			if (m_blend_current != id)
			{
				m_blend_current = id;

				auto item = m_blend_map.find(id);
				if (item == m_blend_map.end())
				{
					CreateBlend(shader);
					item = m_blend_map.find(id);
				}
				BearGraphics::BearRenderInterface::SetBlendState(item->second, BearCore::BearColor::Transparent);
			}

		}
		else
		{
			if (m_blend_current != 0xFFFF)
			{
				BearGraphics::BearRenderInterface::SetBlendState(m_blend_default, BearCore::BearColor::Transparent);
				m_blend_current = 0xFFFF;
			}
		}
	}
}

void BearEngine::BearRender::SetVertex(bsize slot, BearSampler & sampler)
{
	BEAR_ASSERT(sampler.m_texture);
	uint16 id = (static_cast<uint16>(sampler.m_filter) << 8) | (static_cast<uint16>(sampler.m_mode));
	auto item = m_sampler_map.find(id);
	if (item == m_sampler_map.end())
	{
		CreateSampler(sampler);
		item = m_sampler_map.find(id);
	}

	BearGraphics::BearRenderInterface::SetVertexShaderResource(slot, sampler.m_texture->get(), item->second);
}

void BearEngine::BearRender::SetPixel(bsize slot, BearSampler & sampler)
{
	BEAR_ASSERT(sampler.m_texture);
	uint16 id = (static_cast<uint16>(sampler.m_filter) << 8) | (static_cast<uint16>(sampler.m_mode));
	auto item = m_sampler_map.find(id);
	if (item == m_sampler_map.end())
	{
		CreateSampler(sampler);
		item = m_sampler_map.find(id);
	}

	BearGraphics::BearRenderInterface::SetPixelShaderResource(slot, sampler.m_texture->get(), item->second);
}

void BearEngine::BearRender::SetVertex(bsize slot, TypeMatrix type)
{
	switch (type)
	{
	case BearRender::TM_Othro:
		BearGraphics::BearRenderInterface::SetVertexShaderConstants(slot, GeneralViewport->m_sconst_othro);
		break;
	case BearRender::TM_View:
		BearGraphics::BearRenderInterface::SetVertexShaderConstants(slot, m_sconst_view);
		break;
	default:
		break;
	}

}

void BearEngine::BearRender::SetPixel(bsize slot, TypeMatrix type)
{
	switch (type)
	{
	case BearRender::TM_Othro:
		BearGraphics::BearRenderInterface::SetPixelShaderConstants(slot, GeneralViewport->m_sconst_othro);
		break;
	case BearRender::TM_View:
		BearGraphics::BearRenderInterface::SetPixelShaderConstants(slot, m_sconst_view);
		break;
	default:
		break;
	}
}




void BearEngine::BearRender::SetVertex(bsize slot, const BearCore::BearMatrix & matrix)
{
	BearCore::bear_copy(m_sconst_matrix.Lock(), *matrix, sizeof(float) * 16);
	m_sconst_matrix.Unlock();
	BearGraphics::BearRenderInterface::SetVertexShaderConstants(slot, m_sconst_matrix);
}

void BearEngine::BearRender::SetPixel(bsize slot, const BearCore::BearMatrix & matrix)
{
	BearCore::bear_copy(m_sconst_matrix.Lock(), *matrix, sizeof(float)*16);
	m_sconst_matrix.Unlock();
	BearGraphics::BearRenderInterface::SetPixelShaderConstants(slot, m_sconst_matrix);
}

void BearEngine::BearRender::SetView(const BearCore::BearVector4<float>& view)
{
	m_rect_view = view;
	m_view.BuildOrthoOffCenter(view.x1, view.y1, FLT_MIN, 100.f);
	m_view = BearCore::BearMatrix().BuildIdentity().Translation(-view.x, -view.y, 0)*m_view;
	BearCore::bear_copy(m_sconst_view.Lock(), *m_view, sizeof(float) * 16);
	m_sconst_view.Unlock();
}


void BearEngine::BearRender::ClearStats()
{
	m_vertex_state_map.clear_not_free();
	m_vertex_state_current = 0xFFFFFFFFFFFFFFFF;
	m_blend_map.clear();
	m_blend_current = 0xFFFF;
}

void BearEngine::BearRender::Update(float time)
{
	
}

void BearEngine::BearRender::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearRender::Load(const BearCore::BearInputStream * stream)
{
}

void BearEngine::BearRender::CreateBlend(BearShader & shader)
{
	BearGraphics::BearBlendStateInitializer initializer;
	BEAR_ASSERT(shader.m_blend);
	initializer.RenderTarget[0].Enable = true;
	switch (shader.m_blend_dst)
	{
	case BearShader::BF_ZERO:
		initializer.RenderTarget[0].ColorDst= BearGraphics::BF_ZERO;
		break;
	case BearShader::BF_ONE:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_ONE;
		break;
	case BearShader::BF_SRC_COLOR:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_SRC_COLOR;
		break;
	case BearShader::BF_INV_SRC_COLOR:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_INV_SRC_COLOR;
		break;
	case BearShader::BF_SRC_ALPHA:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_SRC_ALPHA;
		break;
	case BearShader::BF_INV_SRC_ALPHA:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_INV_SRC_ALPHA;
		break;
	case BearShader::BF_DEST_ALPHA:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_DEST_ALPHA;
		break;
	case BearShader::BF_INV_DEST_ALPHA:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_INV_DEST_ALPHA;
		break;
	case BearShader::BF_DEST_COLOR:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_DEST_COLOR;
		break;
	case BearShader::BF_INV_DEST_COLOR:
		initializer.RenderTarget[0].ColorDst = BearGraphics::BF_INV_DEST_COLOR;
		break;
	default:
		break;
	}
	switch (shader.m_blend_src)
	{
	case BearShader::BF_ZERO:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_ZERO;
		break;
	case BearShader::BF_ONE:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_ONE;
		break;
	case BearShader::BF_SRC_COLOR:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_SRC_COLOR;
		break;
	case BearShader::BF_INV_SRC_COLOR:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_INV_SRC_COLOR;
		break;
	case BearShader::BF_SRC_ALPHA:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_SRC_ALPHA;
		break;
	case BearShader::BF_INV_SRC_ALPHA:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_INV_SRC_ALPHA;
		break;
	case BearShader::BF_DEST_ALPHA:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_DEST_ALPHA;
		break;
	case BearShader::BF_INV_DEST_ALPHA:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_INV_DEST_ALPHA;
		break;
	case BearShader::BF_DEST_COLOR:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_DEST_COLOR;
		break;
	case BearShader::BF_INV_DEST_COLOR:
		initializer.RenderTarget[0].ColorSrc = BearGraphics::BF_INV_DEST_COLOR;
		break;
	default:
		break;
	}
	uint16 id = (static_cast<uint16>(shader.m_blend_dst) << 8) | (static_cast<uint16>(shader.m_blend_src));
	m_blend_map.insert(id, initializer);
}

void BearEngine::BearRender::CreateSampler(BearSampler & sampler)
{
	BearGraphics::BearSamplerStateInitializer initializer;
	switch (sampler.m_filter)
	{
	case		BearSampler::SF_MAG_MIP_POINT:
		initializer.Filter = BearGraphics::SF_MAG_MIP_POINT;
		break;
	case		BearSampler::SF_MAG_LINEAR_MIP_POINT:
		initializer.Filter = BearGraphics::SF_MAG_LINEAR_MIP_POINT;
		break;
	case		BearSampler::SF_MAG_MIP_LINEAR:
		initializer.Filter = BearGraphics::SF_MAG_MIP_LINEAR;
		break;
	case		BearSampler::SF_ANISOTROPIC:
		initializer.Filter = BearGraphics::SF_ANISOTROPIC;
		break;
	case		BearSampler::SF_COMPARISON_MAG_MIP_POINT:
		initializer.Filter = BearGraphics::SF_COMPARISON_MAG_MIP_POINT;
		break;
	case		BearSampler::SF_COMPARISON_MAG_LINEAR_MIP_POINT:
		initializer.Filter = BearGraphics::SF_COMPARISON_MAG_LINEAR_MIP_POINT;
		break;
	case		BearSampler::SF_COMPARISON_MAG_MIP_LINEAR:
		initializer.Filter = BearGraphics::SF_COMPARISON_MAG_MIP_LINEAR;
		break;
	case		BearSampler::SF_COMPARISON_ANISOTROPIC:
		initializer.Filter = BearGraphics::SF_ANISOTROPIC;
		break;
	default:
		break;
	}
	switch (sampler.m_mode)
	{
	case		BearSampler::SM_WRAP:
		initializer.AddressU = BearGraphics::SAM_WRAP;
		initializer.AddressV = BearGraphics::SAM_WRAP;
		initializer.AddressW = BearGraphics::SAM_WRAP;
		break;
	case		BearSampler::SM_MIRROR:
		initializer.AddressU = BearGraphics::SAM_MIRROR;
		initializer.AddressV = BearGraphics::SAM_MIRROR;
		initializer.AddressW = BearGraphics::SAM_MIRROR;
		break;
	case		BearSampler::SM_CLAMP:
		initializer.AddressU = BearGraphics::SAM_CLAMP;
		initializer.AddressV = BearGraphics::SAM_CLAMP;
		initializer.AddressW = BearGraphics::SAM_CLAMP;
		break;
	case		BearSampler::SM_BORDER:
		initializer.AddressU = BearGraphics::SAM_BORDER;
		initializer.AddressV = BearGraphics::SAM_BORDER;
		initializer.AddressW = BearGraphics::SAM_BORDER;
		break;
	default:
		break;
	}
	uint16 id = (static_cast<uint16>(sampler.m_filter) << 8) | (static_cast<uint16>(sampler.m_mode));
	m_sampler_map.insert(id, initializer);
}
static BearGraphics::BearVertexFormat ConvertVertexFormat(BearEngine::BearShader::VertexFormat format)
{
	switch (format)
	{
	case BearEngine::BearShader::VF_R32_FLOAT:
		return BearGraphics::VF_R32_FLOAT;
		break;
	case BearEngine::BearShader::VF_R32G32_FLOAT:
		return BearGraphics::VF_R32G32_FLOAT;
		break;
	case BearEngine::BearShader::VF_R32G32B32_FLOAT:
		return BearGraphics::VF_R32G32B32_FLOAT;
		break;
	case BearEngine::BearShader::VF_R32G32B32A32_FLOAT:
		return BearGraphics::VF_R32G32B32A32_FLOAT;
		break;
	case BearEngine::BearShader::VF_R32_INT:
		return BearGraphics::VF_R32_INT;
		break;
	case BearEngine::BearShader::VF_R8:
		return BearGraphics::VF_R8;
		break;
	case BearEngine::BearShader::VF_R8G8:
		return BearGraphics::VF_R8G8;
		break;
	case BearEngine::BearShader::VF_R8G8B8A8:
		return BearGraphics::VF_R8G8B8A8;
		break;
	default:
		return BearGraphics::VF_NONE;
		break;
	}
}
static bsize GetSize(BearEngine::BearShader::VertexFormat format)
{
	switch (format)
	{
	case BearEngine::BearShader::VF_R32_FLOAT:
		return sizeof(float)*1;
		break;
	case BearEngine::BearShader::VF_R32G32_FLOAT:
		return sizeof(float) * 2;
		break;
	case BearEngine::BearShader::VF_R32G32B32_FLOAT:
		return sizeof(float) * 3;
		break;
	case BearEngine::BearShader::VF_R32G32B32A32_FLOAT:
		return sizeof(float) * 4;
		break;
	case BearEngine::BearShader::VF_R32_INT:
		return 4;
		break;
	case BearEngine::BearShader::VF_R8:
		return 1;
		break;
	case BearEngine::BearShader::VF_R8G8:
		return 2;
		break;
	case BearEngine::BearShader::VF_R8G8B8A8:
		return 3;
		break;
	default:
		return 0;
		break;
	}
}
void BearEngine::BearRender::CreateVertexState(BearShader & shader)
{
	uint64 id = 0;
	BearGraphics::BearVertexStateInitializer initializer;

	bsize offset= 0;
	for (bsize i = 0; i < 16; i++)
	{
		id |= static_cast<uint64>(shader.m_vertex_state[i]) << 4 * i;
		initializer.Elements[i].IsInstance = false;
		initializer.Elements[i].Name = "element";
		initializer.Elements[i].SemanticIndex = i;
		initializer.Elements[i].Type = ConvertVertexFormat(shader.m_vertex_state[i]);
		initializer.Elements[i].Offset = offset;
		offset += ::GetSize(shader.m_vertex_state[i]);
	}

	BearCore::BearMemoryStream vertexBuffer(**BearCore::FS->Read(TEXT("%app_shaders_cur%"), *shader.m_pixel->get_name().to_string(), TEXT(".vs.bin")));
	m_vertex_state_map.insert(id, BearGraphics::BearVertexStateRef(initializer, vertexBuffer.Begin(), vertexBuffer.Size()));
}