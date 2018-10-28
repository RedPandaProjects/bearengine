#pragma once
namespace BearEngine
{
	class BearTexture2D :public BearResourceWithName
	{
		BEAR_CLASS_NO_COPY(BearTexture2D);
	public:
		static BearTexture2D* Create(const bchar*name);
		void destroy();
		BearCore::BearVector2<float> getSize()const;
	private:
		~BearTexture2D();
		BearTexture2D(const bchar*name); 
		BearCore::BearVector2<float> m_size;
	};
}