#pragma once
namespace BearEngine
{
	class  BearMaterialSpriteAlpha :public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialSpriteAlpha);
	public:
		static BearMaterialSpriteAlpha*Create();
		BearCore::BearVector4<float> TextureUV;
		BearTexture2D *Texture;
		virtual bool suportAlpha();
		virtual void destroy();
	private:
		~BearMaterialSpriteAlpha();
		BearMaterialSpriteAlpha();
		virtual void set();

	};
}