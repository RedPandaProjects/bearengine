#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearObjectList
	{
		BEAR_CLASS_STATIC(BearObjectList);
	public:
		static void Append(BearObject*object);
		static void Destroy(BearObject*object);
		static void DestroyAll();

		static BearObject* Find(const BearName&name);
	};
}