#pragma once
namespace BearEngine
{
	class BearPixelShader :public BearResourceWithName
	{
	public:
		BEAR_CLASS_NO_COPY(BearPixelShader);
		static BearPixelShader* Create(const bchar*name);
		~BearPixelShader();
	private:
		BearPixelShader(const bchar*name);
	};
}