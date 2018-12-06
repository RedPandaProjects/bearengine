#pragma once
namespace BearEngine
{
	class  BearMaterialFont :public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialFont);
	public:
		static BearMaterialFont*Create();
		BearCore::BearVector4<float> TextureUV;
		const BearTexture2D *Texture;
		virtual bool suportAlpha();
		virtual void destroy();
	private:
		~BearMaterialFont();
		BearMaterialFont();
		virtual void set();

	};
}