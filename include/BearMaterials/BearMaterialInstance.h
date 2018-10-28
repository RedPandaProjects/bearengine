#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearMaterialInstance
	{
	public:
		BEAR_CLASS_NO_COPY(BearMaterialInstance);
	
		virtual void set();
		virtual bool suportAlpha();
		virtual void destroy();
		BearCore::BearMatrix Matrix;
	protected:
		~BearMaterialInstance();
		BearMaterialInstance(bsize id);
		BearMaterial*material; 
	};
};