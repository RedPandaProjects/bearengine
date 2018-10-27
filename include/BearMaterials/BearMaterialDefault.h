#pragma once
namespace BearEngine
{
	class  BearMaterialDefault:public BearMaterialInstance
	{
		BEAR_CLASS_NO_COPY(BearMaterialDefault);
	public:
		static BearMaterialDefault*Create();
		~BearMaterialDefault();
		BearTexture2D Texture;
		BearCore::BearMatrix *Matrix;
	private:
		BearMaterialDefault();
		virtual void set();
	};
}	