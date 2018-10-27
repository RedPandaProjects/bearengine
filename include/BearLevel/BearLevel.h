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
		BearCore::BearVector<BearCore::BearMemoryRef<BearEngine::BearSprite>> layer;
	};
	class BEARENGINE_API BearLevel
	{
		BEAR_CLASS_NO_COPY(BearLevel);
	public:
		BearLevel();
		void load(const bchar*name);
		void update(float time);
		void clear();
		~BearLevel();
	private:
		bsize m_width;
		bsize m_height;
		bsize m_tile_width;
		bsize m_tile_height;


		BearCore::BearVector<BearObject*> m_objects_without_name;
		BearCore::BearMap<BearCore::BearStringConteniar,BearObject*> m_objects;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> m_tilesets;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelLayer>> m_layers;

	};
	extern BEARENGINE_API BearLevel*CurrentLevel;
};