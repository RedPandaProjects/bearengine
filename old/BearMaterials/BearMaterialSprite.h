#pragma once
namespace BearEngine
{
	class  BearMaterialSprite:public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialSprite);
	public:
		static BearMaterialSprite*Create();
		BearCore::BearVector4<float> TextureUV;
		BearTexture2D *Texture;
		virtual void destroy();
	private:
		~BearMaterialSprite();
		BearMaterialSprite();
		virtual void set();
		
	};
}