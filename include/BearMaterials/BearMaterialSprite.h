#pragma once
namespace BearEngine
{
	class  BearMaterialSprite:public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialSprite);
	public:
		static BearMaterialSprite*Create();
		~BearMaterialSprite();
		BearCore::BearVector4<float> TextureUV;
		BearTexture2D *Texture;
		BearCore::BearMatrix Matrix;
	private:
		BearMaterialSprite();
		virtual void set();
		
	};
}