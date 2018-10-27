#pragma once
namespace BearEngine
{
	class  BearMaterialSpriteAlpha :public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialSpriteAlpha);
	public:
		static BearMaterialSpriteAlpha*Create();
		~BearMaterialSpriteAlpha();
		BearCore::BearVector4<float> TextureUV;
		BearTexture2D *Texture;
		BearCore::BearMatrix Matrix;
		virtual bool suportAlpha();
	private:
		BearMaterialSpriteAlpha();
		virtual void set();

	};
}