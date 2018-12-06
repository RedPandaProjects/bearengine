#pragma
namespace BearEngine
{

	struct BearLevelLayer
	{
		BearCore::BearVector<BearCore::BearVector2<bsize>> Layer;
	};
	struct BearLevelTileset
	{
		bsize Spacing;
		bsize TileWidth;
		bsize TileHeight;
		BearCore::BearVector<BearTile*> ListTile;
	};
	class BEARENGINE_API BearLevel :public BearObject
	{
		BEAR_OBJECT(BearLevel);
	protected:
		BearLevel(const BearName&type);
		~BearLevel();

		bsize Width;
		bsize Height;
		bsize TileWidth;
		bsize TileHeight;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> Tilesets;
		BearCore::BearMap<BearCore::BearStringConteniar, bsize> MapTilesetsID;
		BearCore::BearVector < BearCore::BearMemoryRef<BearLevelLayer>> Layers;
		BearCore::BearMap<BearCore::BearStringConteniar, bsize> MapLayersID;
	public:
		virtual void Destroy();
		virtual void Update(float time) ;
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		virtual void EndLoad();
		void SpawnObject(const BearName&Type, const BearName&Name, const BearCore::BearVector4<float>&Rect);
		void Clear();
		void Load(const bchar*name);
#ifdef EDITOR
		static void Compile(const bchar*name);
#endif
		BearCore::BearVector < BearObjectLevel*>Objects;
		inline BearCore::BearVector < BearObjectLevel*>::iterator FindObject(const BearName&name)
		{
			auto begin = Objects.begin();
			auto end = Objects.end();
			while (begin != end)
			{
				if ((*begin)->Name == name)
					return begin;
				begin++;
			}
			return end;
		}
		inline BearCore::BearVector < BearObjectLevel*>::iterator NextObject(const BearName&name, BearCore::BearVector < BearObjectLevel*>::iterator pos)
		{
			auto begin = pos;
			auto end = Objects.end();
			while (begin != end)
			{
				if ((*begin)->Name == name)
					return begin;
				begin++;
			}
			return end;
		}
		inline BearCore::BearVector < BearObjectLevel*>::iterator FindObjectByType(const BearName&type)
		{
			auto begin = Objects.begin();
			auto end = Objects.end();
			while (begin != end)
			{
				if ((*begin)->GetType() == type)
					return begin;
				begin++;
			}
			return end;
		}
		inline BearCore::BearVector < BearObjectLevel*>::iterator NextObjectByType(const BearName&type, BearCore::BearVector < BearObjectLevel*>::iterator pos)
		{
			auto begin = pos;
			auto end = Objects.end();
			while (begin != end)
			{
				if ((*begin)->GetType() == type)
					return begin;
				begin++;
			}
			return end;
		}
	private:
		BearTerrain*m_terrain;
		void LoadLevel();
		void LoadLayer();
		void LoadCollision();
		void LoadSpawn();

	};
	BEARENGINE_API extern BearLevel* GLevel;
};