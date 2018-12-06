#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearTile :public BearObject
	{
		BEAR_OBJECT(BearTile);
		BearTile(const BearName&type);
		~BearTile();
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
		BearCore::BearVector4<float> TextureUV;
		void SetTexutre(const BearName&name);
		virtual void Destroy();
		virtual void Update(float time);
	private:
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;
		BearShader m_shader;
		BearSampler m_sampler;
		BearVertex m_vectex[4];
	};
}