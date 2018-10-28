#pragma once
namespace BearEngine
{

	struct BearLevelLayer
	{
		BearCore::BearVector<BearCore::BearVector2<bsize>> layer;
	};
	struct BearLevelTileset
	{
		bsize spacing;
		bsize tile_width;
		bsize tile_height;
		BearCore::BearVector<BearEngine::BearSprite*> layer;
	};
	class BEARENGINE_API BearLevel
	{
		BEAR_CLASS_NO_COPY(BearLevel);
	public:
		static BearLevel*Create(bchar*name);
		void destroy();
		void update(float time);

	private:
		BearLevel(const bchar*name);
		~BearLevel();
		bsize m_width;
		bsize m_height;
		bsize m_tile_width;
		bsize m_tile_height;


		BearCore::BearVector<BearObject*> m_objects_without_name;
		BearCore::BearMap<BearCore::BearStringConteniar,BearObject*> m_objects;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> m_tilesets;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelLayer>> m_layers;
		BearCore::BearVector <BearPhysicsCollider*> m_collider;

	};
	extern BEARENGINE_API BearLevel*CurrentLevel;
};