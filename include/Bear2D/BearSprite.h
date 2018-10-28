#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearSprite
	{
		BEAR_CLASS_NO_COPY(BearSprite);
	public:
		static BearSprite*Create(const bchar*texture, bool alpha = false);
		void destroy();
		void draw();
		inline BearCore::BearVector2<float> &getPosition()
		{
			m_update=true;
			return m_position;
		}
		inline BearCore::BearVector2<float> getPosition()const
		{
			return m_position;
		}
		inline BearCore::BearVector4<float> &getUV()
		{
			m_update=true;
			return m_texture_uv;
		}
		inline BearCore::BearVector4<float> getUV()const
		{
			return m_texture_uv;
		}
		inline BearCore::BearVector2<float>& getSize()
		{
			m_update=true;
			return m_size;
		}	
		inline BearCore::BearVector2<float> getSize()const
		{
			return m_size;
		}
		inline float&getRotation()
		{
			m_update=true;
			return m_rotation;
		}		
		inline float getRotation()const
		{
			return m_rotation;
		}

	private:
		~BearSprite();
		BearSprite(const bchar*texture, bool alpha = false);
		void update();
		bool m_update;
		BearCore::BearVector2<float>  m_position;
		BearCore::BearVector2<float>  m_size;
		BearCore::BearVector4<float>  m_texture_uv;
		float m_rotation;
		BearMaterialInstance *m_material;
	};
}