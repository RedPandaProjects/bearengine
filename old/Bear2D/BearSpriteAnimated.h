#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearSpriteAnimated
	{
		BEAR_CLASS_NO_COPY(BearSpriteAnimated);
	public:
		static BearSpriteAnimated*Create(const bchar*anim);
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
		void destroy();
		void draw(float time);
		inline BearCore::BearVector2<float> &position()
		{
			m_update=true;
			return m_position;
		}
		inline BearCore::BearVector2<float> position()const
		{
			return m_position;
		}
		inline BearCore::BearVector2<float>& size()
		{
			m_update=true;
			return m_size;
		}	
		inline BearCore::BearVector2<float> size()const
		{
			return m_size;
		}
		inline float&rotation()
		{
			m_update = true;
			return m_rotation;
		}
		inline float rotation()const
		{
			return m_rotation;
		}
		void setAnimation(const bchar*name);
	private:
		~BearSpriteAnimated();
		BearSpriteAnimated(const bchar*animate);
		void update();
		bool m_update;
		BearCore::BearVector2<float>  m_position;
		BearCore::BearVector2<float>  m_size;
		BearCore::BearVector2<float>  m_size_local;
		float m_rotation;
		BearMaterialInstance *m_material;
		float m_current_time;
		struct Cut
		{
			BearCore::BearVector2<float> sprite_size;
			BearCore::BearVector4<float> texture_uv;
		};
		struct Animation
		{
			float delay;
			BearCore::BearVector< Cut> cuts;
		};
		BearCore::BearMap<BearCore::BearStringConteniar, Animation> m_animations;
		BearCore::BearMap<BearCore::BearStringConteniar, Animation>::iterator m_current_animation;
		BearCore::BearVector< Cut>::iterator m_current_cut;

	};
}