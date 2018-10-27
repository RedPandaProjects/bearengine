#pragma once
namespace BearEngine
{
	class BearGameFactory
	{
	public:
		virtual BearObject*createObject(const BearObjectType&type)=0;
	};
	extern BEARENGINE_API BearGameFactory *GameFactory;
}
