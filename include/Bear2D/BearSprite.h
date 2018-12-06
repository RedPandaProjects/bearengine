#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearSprite :public BearObject
	{
		BEAR_OBJECT(BearSprite);
		BearSprite(const BearName&type);
		~BearSprite();
	public:
		union
		{	
			BearCore::BearVector4<float> Rect;
			struct
			{
				BearCore::BearVector2<float> Position;
				BearCore::BearVector2<float> Size;
			};
		};
		BearCore::BearVector2<float> Center;
		float Rotation;
		BearCore::BearVector4<float> TextureUV;
		void SetTexutre(const BearName&name);
		virtual void Destroy();
		virtual void Update(float time);
		inline void SetMatrix(BearRender::TypeMatrix matrix)
		{
			m_type_matrix = matrix;
		}
	private:
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;
		BearShader m_shader;
		BearSampler m_sampler;
		BearVertex m_vectex[4];
		BearCore::BearMatrix m_matrix;
		BearRender::TypeMatrix m_type_matrix;
	};
}