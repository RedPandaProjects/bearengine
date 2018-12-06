#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearSpriteAnimater :public BearObject
	{
		BEAR_OBJECT(BearSpriteAnimater);
		BearSpriteAnimater(const BearName&type);
		~BearSpriteAnimater();
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
		float Rotation;
		
		void Play(const bchar*name,bool loop);
		void SetPause(bool pause);
		bool IsPause() const;
		bool IsStop() const;
		void Stop();

		void SetAnimateArray(const BearName&name);
		virtual void Destroy();
		virtual void Update(float time);
	private:
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;

		BearAnimateArray2DRef * m_animate_array;

		BearCore::BearMap<BearCore::BearStringConteniar, BearAnimateArray2D::Animation>::const_iterator m_current_animation;
		BearCore::BearVector< BearAnimateArray2D::Cut>::const_iterator m_current_cut;

		BearShader m_shader;
		BearSampler m_sampler;
		BearCore::BearMatrix m_matrix;

		float m_timer;
		bool m_pause;
		bool m_loop;
	};
}