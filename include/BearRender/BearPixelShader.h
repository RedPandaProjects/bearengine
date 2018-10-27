#pragma once
namespace BearEngine
{
	class BearPixelShader :public BearResourceWithName
	{
		BEAR_CLASS_NO_COPY(BearPixelShader);
		static BearPixelShader* Create(const bchar*name);
		~BearPixelShader();
	private:
		BearPixelShader(const bchar*name);
	};
}