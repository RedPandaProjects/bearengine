#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearFont:public BearResourceWithName
	{
		BEAR_CLASS_NO_COPY(BearFont);
	public:
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
		static BearFont*Create(const bchar*name);
		struct CharInfo
		{
			BearCore::BearVector2<float> size;
			BearCore::BearVector4<float> textureUV;
			float advance;
			BearCore::BearFVector2 position;
		};
		BearCore::BearMap<bchar16, CharInfo>  CharsInfo;
		void destroy();
		inline const BearTexture2D*getTexture() const
		{
			return m_texture;
		}
		inline bsize getSize()const
		{
			return m_size;
		}
	private:
		bsize m_size;
		BearTexture2D*m_texture;
		~BearFont();
		BearFont(const bchar*name);

		
	};
}