#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearShader
	{
		friend class BearRender;
	public:
		enum BlendFactor
		{
			BF_ZERO,
			BF_ONE,
			BF_SRC_COLOR,
			BF_INV_SRC_COLOR,
			BF_SRC_ALPHA,
			BF_INV_SRC_ALPHA,
			BF_DEST_ALPHA,
			BF_INV_DEST_ALPHA,
			BF_DEST_COLOR,
			BF_INV_DEST_COLOR,
		};
		enum VertexFormat
		{
			VF_NONE = 0,
			VF_R32_FLOAT ,
			VF_R32G32_FLOAT,
			VF_R32G32B32_FLOAT,
			VF_R32G32B32A32_FLOAT,
			VF_R32_INT,
			VF_R8,
			VF_R8G8,
			VF_R8G8B8A8,
		};
		BearShader();
		BearShader(const BearName&vs, const BearName&ps);
		void swap(BearShader&right);
		BearShader(BearShader&right);
		BearShader&operator=(BearShader&right);
		~BearShader();
		inline BearShader& SetBlend(BlendFactor blend_src, BlendFactor blend_dst)
		{
			m_blend = true;
			m_blend_src = blend_src;
			m_blend_dst = blend_dst;
			return*this;
		}
		inline BearShader&  SetVertexState(bsize slot, VertexFormat format)
		{
			BEAR_ASSERT(slot < 16);
			m_vertex_state[slot] = format;
			return*this;
		}
	private:
		VertexFormat m_vertex_state[16];
		BearPixelShaderRef*m_pixel;
		BearVertexShaderRef*m_vertex;
		BlendFactor m_blend_src;
		BlendFactor m_blend_dst;
		bool m_blend;
	};
};