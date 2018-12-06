#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearRenderText :public BearObject
	{
		BEAR_OBJECT(BearRenderText);
		BearRenderText(const BearName&type);
		~BearRenderText();
	public:
		BearCore::BearVector2<float> Position;
		BearCore::BearString Text;
		float MaxWidth;
		void SetFont(const BearName&name);
		virtual void Destroy();
		virtual void Update(float time);
		inline void SetMatrix(BearRender::TypeMatrix matrix)
		{
			m_type_matrix = matrix;
		}
		inline bsize GetSizeFont() const
		{
			if (m_font)return m_font->get()->GetSize();
			return 0;
		}
	private:
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;
		BearShader m_shader;
		BearSampler m_sampler;
		BearFontRef*m_font;
		BearVertex m_vectex[4];
		BearRender::TypeMatrix m_type_matrix;
	};
}