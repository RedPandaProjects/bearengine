#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearRender :public BearObject
	{
		BEAR_OBJECT(BearRender);
		BearRender(const BearName&type);
		~BearRender();
	public:
		enum TypeMatrix
		{
			TM_Othro,
			TM_View,
		};
		virtual void Destroy() override;
		void SetShader(BearShader&shader);
		void SetVertex(bsize slot,BearSampler&sampler);
		void SetPixel(bsize slot, BearSampler&sampler);

		void SetVertex(bsize slot, TypeMatrix type);
		void SetPixel(bsize slot, TypeMatrix type);
		void SetVertex(bsize slot, const BearCore::BearMatrix&matrix);
		void SetPixel(bsize slot,const BearCore::BearMatrix&matrix);

		void SetView(const BearCore::BearVector4<float>&view);
		inline void SetView(float x,float y,float width ,float height)
		{
			SetView(BearCore::BearVector4<float>(x, y, width, height));
		}
		inline const BearCore::BearVector4<float>&GetView()
		{
			return m_rect_view;
		}

	private:
		virtual void Update(float time) override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream) override;


		BearCore::BearString Render;
		BearCore::BearMatrix m_view;

		BearCore::BearVector4<float> m_rect_view;

		BearGraphics::BearShaderConstantsRef m_sconst_view;
		BearGraphics::BearShaderConstantsRef m_sconst_matrix;

		void CreateBlend(BearShader&shader);
		BearCore::BearMap<uint16, BearGraphics::BearBlendStateRef> m_blend_map;
		uint16 m_blend_current;
		BearGraphics::BearBlendStateRef m_blend_default;

		void CreateSampler(BearSampler&shader);
		BearCore::BearMap<uint16, BearGraphics::BearSamplerStateRef> m_sampler_map;

		void CreateVertexState(BearShader&shader);
		uint64 m_vertex_state_current;
		BearCore::BearMap < uint64, BearGraphics::BearVertexStateRef> m_vertex_state_map;



	};
	BEARENGINE_API extern BearRender*GRender;
}