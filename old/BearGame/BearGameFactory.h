#pragma once
namespace BearEngine
{
	class BEARPROJECT_EXPORT BearGameFactory
	{
	public:
		virtual void initialize();
		virtual void destroy();
		BearObject*getObject(const BearObjectType&type);
		virtual const bchar*getGameName();
	protected:
		BearCore::BearMap<BearObjectType,BearObject*> objects;
	};
	extern BEARENGINE_API BearGameFactory *GameFactory;
}
