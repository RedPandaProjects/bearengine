#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearAnimateArray2D
	{

	public:
		BearAnimateArray2D();
		BearAnimateArray2D(const bchar*name);
		~BearAnimateArray2D();
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
		void clear();
		void swap(BearAnimateArray2D&right);
		void copy(const BearAnimateArray2D&right);

		BearAnimateArray2D(BearAnimateArray2D&&right);
		BearAnimateArray2D(const BearAnimateArray2D&right);

		BearAnimateArray2D& operator=(const BearAnimateArray2D&right);
		BearAnimateArray2D& operator=(BearAnimateArray2D&&right);

		inline const BearName&GetTextureName() const
		{
			return m_texture_name;
		}

		struct Cut
		{
			BearCore::BearVector2<float> SpriteSize;
			BearCore::BearVector4<float> TextureUV;
		};
		struct Animation
		{
			float delay;
			BearCore::BearVector< Cut> cuts;
		};
		BearCore::BearMap<BearCore::BearStringConteniar, Animation> Animations;
	private:
		BearName m_texture_name;
	};
}