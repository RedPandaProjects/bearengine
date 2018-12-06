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
		inline BearCore::BearVector2<float> &position()
		{
			m_update=true;
			return m_position;
		}
		inline BearCore::BearVector2<float> position()const
		{
			return m_position;
		}
		inline BearCore::BearVector4<float> &textureUV()
		{
			m_update=true;
			return m_texture_uv;
		}
		inline BearCore::BearVector4<float> textureUV()const
		{
			return m_texture_uv;
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
			m_update=true;
			return m_rotation;
		}		
		inline float rotation()const
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