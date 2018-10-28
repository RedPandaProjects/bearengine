#pragma once
namespace BearEngine
{
	class BearPixelShader :public BearResourceWithName
	{
	public:
		BEAR_CLASS_NO_COPY(BearPixelShader);
		static BearPixelShader* Create(const bchar*name);
		void destroy();
	private:
		~BearPixelShader();
		BearPixelShader(const bchar*name);
	};
}