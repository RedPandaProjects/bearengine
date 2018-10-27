#pragma once
namespace BearEngine
{
	class  BearMaterialController
	{
	public:
	enum MaterialType
	{
		MT_Default=0,
		MT_Sprite,
		MT_SpriteAlpha,
		MT_Other,
	};
	static void Initialize();
	static void Destory();
	BEARENGINE_API static void SetMaterial(BearMaterial*mat,bsize id);
	static BearMaterial* GetMaterial(bsize id);
};