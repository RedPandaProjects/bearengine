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
		BearCore::BearVector<BearEngine::BearSprite*> tile;
	};
	class BEARENGINE_API BearLevel
	{
		BEAR_CLASS_NO_COPY(BearLevel);
	public:
		static BearLevel*Create(bchar*name);
		void destroy();
		void update(float time);
		BearCore::BearVector <BearPhysicsCollider*> colliders;
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
	private:
		BearLevel(const bchar*name);
		~BearLevel();

		bsize m_width;
		bsize m_height;
		bsize m_tile_width;
		bsize m_tile_height;

		void loadLevel();
		void loadLayer();
		void loadCollision();
		void loadSpawn();

		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> m_tilesets;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelLayer>> m_layers;


	};
	extern BEARENGINE_API BearLevel*CurrentLevel;
};