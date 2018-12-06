#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearEditor :public BearEngine
	{
		BEAR_OBJECT(BearEditor);
		BearEditor(const BearName&type);
		~BearEditor();
		virtual void Loop();
		virtual void Initialize(bchar**V, int32 C);
		virtual void Destroy();
		void CompileTextures(const bchar*type);
		void CompileTexture(const bchar*file,BearGraphics::BearTexturePixelFormat format);
	};
}