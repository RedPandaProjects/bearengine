#include "BearEngine.hpp"

BearEngine::BearMaterial * BearEngine::BearMaterial::Create(const bchar * px, const bchar * vs)
{
	auto type = BearCore::bear_alloc< BearMaterial>(1);
	return new(type)BearMaterial(px,vs);
}

BearEngine::BearMaterial::~BearMaterial()
{
	BearCore::bear_delete(m_pixel_shader);
	BearCore::bear_delete(m_vertex_shader);
}

void BearEngine::BearMaterial::appendValue(const char * name, Shader shader, ShaderType shader_type, bsize id)
{
	Value value;
	BearCore::bear_copy(value.name, name,BearCore::bear_max( BearCore::BearString::GetSize(name)+1,bsize(64)));
	value.shader = shader;
	value.shader_type = shader_type;
	m_textures.insert(id, value);
}

void BearEngine::BearMaterial::set()
{
	BearRender::Set(m_pixel_shader);
	BearRender::Set(m_vertex_shader);
}

BearEngine::BearMaterial::BearMaterial(const bchar* pixel,const bchar*vertex)
{
	m_pixel_shader = BearPixelShader::Create(pixel);
	m_vertex_shader = BearVertexShader::Create(vertex);
}

void BearEngine::BearMaterial::setValue(bsize id, void * data)
{
	auto item = m_textures[id];
	switch (item.shader)
	{
	case S_Pixel:
		switch (item.shader_type)
		{
		case ST_Matrix:
		{

			break;
		}
		case ST_Texture:
		{
			BearRender::SetPS(item.name, reinterpret_cast<BearTexture2D*>(data));

		}break;
		case ST_R:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInPixelShader(item.name, value[0]);
		}	break;
		case ST_RG:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInPixelShader(item.name, value[0], value[1]);
		}	break;
		case ST_RGB:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInPixelShader(item.name, value[0], value[1], value[2]);
		}	break;
		case ST_RGBA:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInPixelShader(item.name, value[0], value[1], value[2], value[3]);
		}
		break;
		};
		break;
	case S_Vertex:
		switch (item.shader_type)
		{
		case ST_Matrix:
		{
			BearGraphics::BearRenderInterface::SetItemInVertexShader(item.name, *reinterpret_cast<BearCore::BearMatrix*>(data));
		} 	break;
		case ST_Texture:
		{
			BearRender::SetVS(item.name, reinterpret_cast<BearTexture2D*>(data));
		}	break;
		case ST_R:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInVertexShader(item.name, value[0]);
		}	break;
		case ST_RG:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInVertexShader(item.name, value[0], value[1]);
		}	break;
		case ST_RGB:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInVertexShader(item.name, value[0], value[1], value[2]);
		}	break;
		case ST_RGBA:
		{
			float*value = reinterpret_cast<float*>(data);
			BearGraphics::BearRenderInterface::SetItemInVertexShader(item.name, value[0], value[1], value[2], value[3]);
		}
		break;
		};
		break;
	};
};
