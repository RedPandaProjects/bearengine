#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearFont 
	{
	
	public:
		BearFont();
		BearFont(const bchar*name);
		~BearFont();
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
		void clear();
		void swap(BearFont&right);
		void copy(const BearFont&right);

		BearFont(BearFont&&right);
		BearFont(const BearFont&right);

		BearFont& operator=(const BearFont&right);
		BearFont& operator=( BearFont&&right);

		struct CharInfo
		{
			BearCore::BearVector2<float> size;
			BearCore::BearVector4<float> textureUV;
			float advance;
			BearCore::BearFVector2 position;
		};
		BearCore::BearMap<bchar16, CharInfo>  CharsInfo;
		inline const BearName&GetTextureName() const
		{
			return m_texture_name;
		}
		inline bsize GetSize()const
		{
			return m_size;
		}
	private:
		bsize m_size;
		BearName m_texture_name;
	};
}