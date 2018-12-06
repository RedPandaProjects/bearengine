#include "BearEngine.hpp"
 BEARENGINE_API BearEngine::BearLevel*BearEngine::CurrentLevel=0;
extern BearCore::BearFileSystem *FS ;
static uint32 level_version = 1;
static uint32 spawn_version = 1;
extern  BearCore::BearVector4<float> GlobalView;
BearEngine::BearLevel::BearLevel(const bchar*name)
{
	FS->subPath(TEXT("%level%"));
	FS->appendPath(TEXT("%level%"), name, TEXT("%levels%"), 0);
	BearCore::BearDebug::Printf(TEXT("Level set [%s]"), name);
	loadLevel();
	loadLayer();
	loadCollision();
	loadSpawn();
	
}

BearEngine::BearLevel * BearEngine::BearLevel::Create(bchar * name)
{
	auto th=BearCore::bear_alloc<BearLevel>(1);
	return new(th)BearLevel(name);
}

void BearEngine::BearLevel::destroy()
{
	{
		auto begin = m_tilesets.begin();
		auto end = m_tilesets.end();
		while (begin != end)
		{
			auto beginl = (*begin)->tile.begin();
			auto endl = (*begin)->tile.end();
			while (beginl != endl)
			{
				(*beginl)->destroy();
				beginl++;
			}
			begin++;
		}
	}
	{
		auto begin = colliders.begin();
		auto end = colliders.end();
		while (begin != end)
		{
			(*begin)->destroy();
			begin++;
		}
	}
	colliders.clear();
	m_layers.clear();
	m_tilesets.clear();
	this->~BearLevel();
	BearObjectList::DestroyAll();
	BearCore::bear_free(this);
}
inline bool frustum(float x, float y, float x1 , float y1)
{
	if (x + x1 > GlobalView.x&&x < GlobalView.x1+ GlobalView.x)
		if (y + y1 >GlobalView.y&&y <GlobalView.y1+ GlobalView.y)
			return true;
	return false;
}
void BearEngine::BearLevel::update(float time)
{
	for (bsize i = 0; i < m_layers.size(); i++)
	{
		bsize x = 0;
		bsize y = 0;
		auto begin = m_layers[i]->layer.begin();
		auto end = m_layers[i]->layer.end();
		while (begin != end)
		{
			if (begin->x&&frustum(static_cast<float>(x*m_tile_width), static_cast<float>(y*m_tile_height), static_cast<float>(m_tilesets[begin->x - 1]->tile_width), static_cast<float>(m_tilesets[begin->x - 1]->tile_height)))
			{
				auto&sprite = m_tilesets[begin->x - 1]->tile[begin->y];
				sprite->position().set(static_cast<float>(x*m_tile_width), static_cast<float>(y*m_tile_height));
				sprite->draw();
			
			}
			x++;
			if (x == m_width) {
				x = 0; y++;
			}
			begin++;
		}
	}


}

#ifdef EDITOR
void BearEngine::BearLevel::Compile(const bchar * name)
{
	FS->subPath(TEXT("%level%"));
	FS->appendPath(TEXT("%level%"), name, TEXT("%levels%"), 0);
	BearCore::BearDebug::Printf(TEXT("Compile level [%s] start"), name);
	BearCore::BearXML XML;
	BearCore::BearString out1, out2;

	FS->createPath(TEXT("%level%"), 0);

	BEAR_ASSERT(XML.loadFromStream(**FS->read(TEXT("%import%"),name,TEXT(".tmx")),BearCore::BearEncoding::UTF8, out1, out2));

	auto LevelFile = FS->write(TEXT("%level%"), TEXT("level"),0);
	auto LayerFile = FS->write(TEXT("%level%"), TEXT("level.layer"),0);
	auto CollisionFile = FS->write(TEXT("%level%"), TEXT("level.collision"),0);
	auto SpawnFile = FS->write(TEXT("%level%"), TEXT("level.spawn"),0);


	auto map = XML.getNode("map");
	BEAR_ASSERT(map);
	uint32 width = 0;
	XML.getAtribute(map, "width", TEXT("0")).scanf(TEXT("%u"), &width);
	BEAR_ASSERT(width);
	uint32 height = 0;
	XML.getAtribute(map, "height", TEXT("0")).scanf(TEXT("%u"), &height);
	BEAR_ASSERT(height);
	uint32 tile_width = 0;
	XML.getAtribute(map, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &tile_width);
	BEAR_ASSERT(tile_width);
	uint32 tile_height = 0;
	XML.getAtribute(map, "tileheight", TEXT("0")).scanf(TEXT("%u"), &tile_height);
	BEAR_ASSERT(tile_height);

	BearCore::BearDebug::Printf(TEXT("Size [%ux%u] TileSize [%ux%u]"), width, height, tile_width, tile_height);
	BearCore::BearDebug::Printf(TEXT("Saving... Level"));
	LevelFile->writeUint32(level_version);
	LevelFile->writeUint32(width);
	LevelFile->writeUint32(height);
	LevelFile->writeUint32(tile_width);
	LevelFile->writeUint32(tile_height);
	bsize tell_count_tile = LevelFile->tell();
	LevelFile->writeUint32(0);
	BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> tilesets;


	auto tileset = XML.getNode(map, "tileset");
	BearCore::BearVector<uint32> tile_level;
	uint32 count_tileset = 0;
	while (tileset)
	{
		uint32 firstgid = 0, spacing=0, tileset_width=0, tileset_height=0,width_texture = 0, height_texture = 0;
		XML.getAtribute(tileset, "firstgid", TEXT("0")).scanf(TEXT("%u"), &firstgid);
		BEAR_ASSERT(firstgid);

		XML.getAtribute(tileset, "spacing", TEXT("0")).scanf(TEXT("%u"), &spacing);
		XML.getAtribute(tileset, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &tileset_width);
		XML.getAtribute(tileset, "tileheight", TEXT("0")).scanf(TEXT("%u"), &tileset_height);

		auto image = XML.getNode(tileset, "image");
		BEAR_ASSERT(image);

		BearCore::BearString source = BearCore::BearFileManager::GetFileName(*XML.getAtribute(image, "source", TEXT("")));
		if (source.to_char_with_end(TEXT('/')))
			source++;
		else
			source.seek(0);
		BEAR_ASSERT(source.size());

		XML.getAtribute(image, "width", TEXT("0")).scanf(TEXT("%d"), &width_texture);
		BEAR_ASSERT(width_texture);
		XML.getAtribute(image, "height", TEXT("0")).scanf(TEXT("%d"), &height_texture);
		BEAR_ASSERT(height_texture);

		LevelFile->writeString(*source, BearCore::BearEncoding::UTF16);
		LevelFile->writeUint32(tileset_width);	LevelFile->writeUint32(tileset_height);
		LevelFile->writeUint32(spacing);

		uint32 cout_x = width_texture / (tileset_width);
		uint32 cout_y = height_texture / (tileset_height);

		LevelFile->writeUint32(cout_x*cout_y);

		for (uint32 y = 0; y < cout_y; y++)
			for (uint32 x = 0; x < cout_x; x++)
			{
				LevelFile->writeFloat(static_cast<float>((tileset_height + spacing)*x) / static_cast<float>(width_texture));
				LevelFile->writeFloat(static_cast<float>((tileset_height + spacing)*y) / static_cast<float>(height_texture));
				LevelFile->writeFloat(static_cast<float>(tileset_width) / static_cast<float>(width_texture));
				LevelFile->writeFloat(static_cast<float>(tileset_height) / static_cast<float>(height_texture));
			
			}
		BEAR_ASSERT(BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), firstgid) == tile_level.end());
		tile_level.push_back(firstgid);
		tileset = XML.nextNode(tileset, "tileset");
		count_tileset++;
	}
	LevelFile->seek(tell_count_tile);
	LevelFile->writeUint32(count_tileset);
	LevelFile.clear();

	BearCore::BearDebug::Printf(TEXT("Saving... level.layer"));
	LayerFile->writeUint32(0);
	auto layer = XML.getNode(map, "layer");
	uint32 count_layer = 0;
	while (layer)
	{
		auto data = XML.getNode(layer, "data");
		auto tile = XML.getNode(data, "tile");
		while (tile)
		{
			uint32 gid = 0;
			XML.getAtribute(tile, "gid", TEXT("0")).scanf(TEXT("%u"), &gid);
			if (gid)
			{
				auto item = BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), gid + 1);

				LayerFile->writeUint32(static_cast<uint32>(item - tile_level.begin()));
				LayerFile->writeUint32(gid - *tile_level.begin());
			}
			else
			{
				LayerFile->writeUint32(0);
				LayerFile->writeUint32(0);
			}
			tile = XML.nextNode(tile, "tile");
		}
		count_layer++;
		layer = XML.nextNode(layer, "layer");
	};
	LayerFile->seek(0);
	LayerFile->writeUint32(count_layer);
	LayerFile.clear();

	BearCore::BearDebug::Printf(TEXT("Size layer[%u] byte"), count_layer*width*height*sizeof(uint32)*2);

	BearCore::BearDebug::Printf(TEXT("Saving... level.collision and level.spawn"));

	CollisionFile->writeUint32(0);
	uint32 count_collider = 0;
	SpawnFile->writeUint32(level_version);
	SpawnFile->writeUint32(0);
	uint32 count_spawn = 0;

	auto objectgroup = XML.getNode(map, "objectgroup");
	if (!objectgroup)return;
	auto object = XML.getNode(objectgroup, "object");
	while (object)
	{
		bint x_obj = 0, y_obj = 0;
		bsize width_obj = 0, height_obj = 0;
		XML.getAtribute(object, "x", TEXT("0")).scanf(TEXT("%d"), &x_obj);
		XML.getAtribute(object, "y", TEXT("0")).scanf(TEXT("%d"), &y_obj);

		XML.getAtribute(object, "width", TEXT("0")).scanf(TEXT("%u"), &width_obj);
		XML.getAtribute(object, "height", TEXT("0")).scanf(TEXT("%u"), &height_obj);
		BearCore::BearString type, objname;
		type = XML.getAtribute(object, "type", TEXT(""));
		BEAR_ASSERT(type.size());
		objname = XML.getAtribute(object, "name", TEXT(""));
		if (type == TEXT("Collider"))
		{
			if (width_obj&&height_obj)
			{
				CollisionFile->writeFloat((float)x_obj);	CollisionFile->writeFloat((float)y_obj); CollisionFile->writeFloat((float)width_obj); CollisionFile->writeFloat((float)height_obj);
				count_collider++;
			}
		}
		else
		{
			count_spawn++;
			SpawnFile->writeInt64(BearObjectType(*BearCore::BearEncoding::ToANSI(*type)).to_uint64());
			SpawnFile->writeString(objname, BearCore::BearEncoding::UTF16);
			SpawnFile->writeFloat((float)x_obj); SpawnFile->writeFloat((float)y_obj - (float)height_obj);
		}
		object = XML.nextNode(object, "object");
	}
	BearCore::BearDebug::Printf(TEXT("Size spawn [%u]"), count_spawn);
	BearCore::BearDebug::Printf(TEXT("Size collider [%u]"), count_collider);
	SpawnFile->seek(4);
	SpawnFile->writeUint32(count_spawn);
	SpawnFile.clear();
	CollisionFile->seek(0);	
	CollisionFile->writeUint32(count_collider);
	CollisionFile.clear();
	BearCore::BearDebug::Printf(TEXT("Compile level end"));
}
#endif


BearEngine::BearLevel::~BearLevel()
{
}

void BearEngine::BearLevel::loadLevel()
{
	BearCore::BearDebug::Printf(TEXT("Loading... Level"));
	auto LevelFile = FS->read(TEXT("%level%"), TEXT("level"));
	BEAR_ASSERT(LevelFile->readUint32() == level_version);
	m_width=LevelFile->readUint32();
	m_height =LevelFile->readUint32();
	m_tile_width= LevelFile->readUint32();
	m_tile_height = LevelFile->readUint32();
	uint32 count_tileset = LevelFile->readUint32();
	BearCore::BearString texture;
	for (uint32 i = 0; i < count_tileset; i++)
	{
		texture.clear_no_free();
		LevelFile->readString(texture);
		BearLevelTileset*tileset = BearCore::bear_new< BearLevelTileset>();
		tileset->tile_width = LevelFile->readUint32();
		tileset->tile_height = LevelFile->readUint32();
		tileset->spacing= LevelFile->readUint32();
		uint32 count_tile = LevelFile->readUint32();;
		for (uint32 a = 0; a < count_tile; a++)
		{
			BearCore::BearVector4<float> UV;
			UV.x = LevelFile->readFloat();
			UV.y = LevelFile->readFloat();
			UV.x1 = LevelFile->readFloat();
			UV.y1 = LevelFile->readFloat();
			BearSprite*tile = BearSprite::Create(*texture);
			tile->size().set(static_cast<float>(tileset->tile_width), static_cast<float>(tileset->tile_height));
			tile->textureUV() = UV;
			tileset->tile.push_back(tile);
		}
		m_tilesets.push_back(tileset);
	}

}

void BearEngine::BearLevel::loadLayer()
{
	BearCore::BearDebug::Printf(TEXT("Loading... Level.Layer"));
	auto LayerFile = FS->read(TEXT("%level%"), TEXT("level.layer"));
	uint32 count = LayerFile->readUint32();
	for (uint32 i = 0; i < count; i++)
	{
		BearLevelLayer*layer = BearCore::bear_new< BearLevelLayer>();
		bsize count_l = m_width * m_height;
		for (bsize a= 0; a < count_l; a++)
		{
			BearCore::BearVector2<bsize> t;
			t.x = LayerFile->readUint32();
			t.y = LayerFile->readUint32();
			layer->layer.push_back(t);
		}
		m_layers.push_back(layer);
	}
}

void BearEngine::BearLevel::loadCollision()
{
	BearCore::BearDebug::Printf(TEXT("Loading... Level.Collision"));
	auto CollisionFile = FS->read(TEXT("%level%"), TEXT("level.collision"));
	uint32 count = CollisionFile->readUint32();
	for (uint32 i = 0; i < count; i++)
	{
		BearCore::BearVector2<float> pos,size;
		pos.x = CollisionFile->readFloat();
		pos.y = CollisionFile->readFloat();
		size.x = CollisionFile->readFloat()/2;
		size.y = CollisionFile->readFloat()/2;
		colliders.push_back(BearPhysicsCollider::Create(pos, size, size));
	}
}

void BearEngine::BearLevel::loadSpawn()
{
	BearCore::BearDebug::Printf(TEXT("Loading... Level.Spawn"));
	auto SpawnFile = FS->read(TEXT("%level%"), TEXT("level.spawn"));
	BEAR_ASSERT(SpawnFile->readUint32() == spawn_version);
	uint32 count = SpawnFile->readUint32();
	BearCore::BearString  objname;
	for (uint32 i = 0; i < count; i++)
	{
		BearObjectType objtype;
		objtype.to_uint64() = SpawnFile->readInt64();
		objname.clear_no_free();
		SpawnFile->readString(objname);
		BearCore::BearVector2<float> pos;
		pos.x = SpawnFile->readFloat();
		pos.y = SpawnFile->readFloat();
		BearObjectList::Append( GameFactory->getObject(objtype)->Create(BearName(*objname),pos));
	}

}
