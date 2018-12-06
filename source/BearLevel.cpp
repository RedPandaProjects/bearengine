#include "BearEngine.hpp"
static uint32 level_version = 4;
static uint32 spawn_version = 2;

BEARENGINE_API BearEngine::BearLevel* BearEngine::GLevel=0;

#ifdef EDITOR
BearEngine::BearLevel::BearLevel(const BearName & type):BearObject(type,BO_OnlyOne),Width(0),Height(0),TileWidth(0),TileHeight(0)
{
	m_terrain = GObjectManager->Create<BearTerrain>(TEXT("BearEngine::BearTerrain"));
}
BearEngine::BearLevel::~BearLevel()
{
	Clear();
	m_terrain->Destroy();
}
void BearEngine::BearLevel::Compile(const bchar * name)
{
	BearCore::FS->SubPath(TEXT("%level%"));
	BearCore::FS->AppendPath(TEXT("%level%"), name, TEXT("%levels%"), 0);
	BearCore::BearLog::Printf(TEXT("Compile level [%s] start"), name);
	BearCore::BearXML XML;
	BearCore::BearString out1, out2;

	BearCore::FS->CreatePath(TEXT("%level%"), 0);

	BEAR_ASSERT(XML.LoadFromStream(**BearCore::FS->Read(TEXT("%import%"), name, TEXT(".tmx")), BearCore::BearEncoding::UTF8, out1, out2));

	auto LevelFile = BearCore::FS->Write(TEXT("%level%"), TEXT("level"), 0);
	auto LayerFile = BearCore::FS->Write(TEXT("%level%"), TEXT("level.layer"), 0);
	auto CollisionFile = BearCore::FS->Write(TEXT("%level%"), TEXT("level.collision"), 0);
	auto SpawnFile = BearCore::FS->Write(TEXT("%level%"), TEXT("level.spawn"), 0);


	auto map = XML.GetNode("map");
	BEAR_ASSERT(map);
	uint32 width = 0;
	XML.GetAtribute(map, "width", TEXT("0")).scanf(TEXT("%u"), &width);
	BEAR_ASSERT(width);
	uint32 height = 0;
	XML.GetAtribute(map, "height", TEXT("0")).scanf(TEXT("%u"), &height);
	BEAR_ASSERT(height);
	uint32 tile_width = 0;
	XML.GetAtribute(map, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &tile_width);
	BEAR_ASSERT(tile_width);
	uint32 tile_height = 0;
	XML.GetAtribute(map, "tileheight", TEXT("0")).scanf(TEXT("%u"), &tile_height);
	BEAR_ASSERT(tile_height);

	BearCore::BearLog::Printf(TEXT("Size [%ux%u] TileSize [%ux%u]"), width, height, tile_width, tile_height);
	BearCore::BearLog::Printf(TEXT("Saving... Level"));
	LevelFile->WriteUint32(level_version);
	LevelFile->WriteUint32(width);
	LevelFile->WriteUint32(height);
	LevelFile->WriteUint32(tile_width);
	LevelFile->WriteUint32(tile_height);



	bsize tell_count_tile = LevelFile->Tell();
	LevelFile->WriteUint32(0);
	BearCore::BearVector < BearCore::BearMemoryRef<BearLevelTileset>> tilesets;

	BearCore::BearString name_terrain,terrain_texture1, terrain_texture2, terrain_texture3;

	auto imagelayer = XML.GetNode(map, "imagelayer");
	while (imagelayer)
	{
		if (XML.GetAtribute(imagelayer, "name", TEXT("")) == TEXT("terrain"))
		{
			auto image = XML.GetNode(imagelayer, "image");
			BEAR_ASSERT(image);
			BearCore::BearString source = BearCore::BearFileManager::GetFileName(*XML.GetAtribute(image, "source", TEXT("")));
			if (source.to_char_with_end(TEXT('/')))
				source++;
			else
				source.seek(0);
			name_terrain = source;
			auto properties = XML.GetNode(imagelayer, "properties"); 
			auto property = XML.GetNode(properties, "property");
			while (property)
			{
				auto name_p = XML.GetAtribute(property, "name", TEXT(""));
				if (name_p == TEXT("texture1"))
				{
					terrain_texture1 = XML.GetAtribute(property, "value", TEXT(""));
				}
				else if (name_p == TEXT("texture2"))
				{
					terrain_texture2= XML.GetAtribute(property, "value", TEXT(""));
				}
				else if (name_p == TEXT("texture3"))
				{
					terrain_texture3 = XML.GetAtribute(property, "value", TEXT(""));
				}
				property = XML.NextNode(property, "property");
			}
			break;
		}
		imagelayer = XML.NextNode(imagelayer, "imagelayer");
	}
	
	LevelFile->WriteString(name_terrain,BearCore::BearEncoding::UTF16);
	LevelFile->WriteString(terrain_texture1, BearCore::BearEncoding::UTF16);
	LevelFile->WriteString(terrain_texture2, BearCore::BearEncoding::UTF16);
	LevelFile->WriteString(terrain_texture3, BearCore::BearEncoding::UTF16);
	auto tileset = XML.GetNode(map, "tileset");
	BearCore::BearVector<uint32> tile_level;
	uint32 count_tileset = 0;
	while (tileset)
	{
		uint32 firstgid = 0, spacing = 0, tileset_width = 0, tileset_height = 0, width_texture = 0, height_texture = 0;
		XML.GetAtribute(tileset, "firstgid", TEXT("0")).scanf(TEXT("%u"), &firstgid);
		BEAR_ASSERT(firstgid);

		XML.GetAtribute(tileset, "spacing", TEXT("0")).scanf(TEXT("%u"), &spacing);
		XML.GetAtribute(tileset, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &tileset_width);
		XML.GetAtribute(tileset, "tileheight", TEXT("0")).scanf(TEXT("%u"), &tileset_height);

		auto image = XML.GetNode(tileset, "image");
		BEAR_ASSERT(image);

		BearCore::BearString source = BearCore::BearFileManager::GetFileName(*XML.GetAtribute(image, "source", TEXT("")));
		if (source.to_char_with_end(TEXT('/')))
			source++;
		else
			source.seek(0);
		BEAR_ASSERT(source.size());

		XML.GetAtribute(image, "width", TEXT("0")).scanf(TEXT("%d"), &width_texture);
		BEAR_ASSERT(width_texture);
		XML.GetAtribute(image, "height", TEXT("0")).scanf(TEXT("%d"), &height_texture);
		BEAR_ASSERT(height_texture);

		LevelFile->WriteString(*source, BearCore::BearEncoding::UTF16);
		LevelFile->WriteUint32(tileset_width);	LevelFile->WriteUint32(tileset_height);
		LevelFile->WriteUint32(spacing);

		uint32 cout_x = width_texture / (tileset_width);
		uint32 cout_y = height_texture / (tileset_height);

		LevelFile->WriteUint32(cout_x*cout_y);

		for (uint32 y = 0; y < cout_y; y++)
			for (uint32 x = 0; x < cout_x; x++)
			{
				LevelFile->WriteFloat(static_cast<float>((tileset_width + spacing)*x) / static_cast<float>(width_texture));
				LevelFile->WriteFloat(static_cast<float>((tileset_height + spacing)*y) / static_cast<float>(height_texture));
				LevelFile->WriteFloat(static_cast<float>(tileset_width) / static_cast<float>(width_texture));
				LevelFile->WriteFloat(static_cast<float>(tileset_height) / static_cast<float>(height_texture));

			}
		BEAR_ASSERT(BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), firstgid) == tile_level.end());
		tile_level.push_back(firstgid);
		tileset = XML.NextNode(tileset, "tileset");
		count_tileset++;
	}
	LevelFile->Seek(tell_count_tile);
	LevelFile->WriteUint32(count_tileset);
	LevelFile.clear();

	BearCore::BearLog::Printf(TEXT("Saving... level.layer"));
	LayerFile->WriteUint32(0);
	auto layer = XML.GetNode(map, "layer");
	uint32 count_layer = 0;
	while (layer)
	{
		BearCore::BearString name_l = BearCore::BearFileManager::GetFileName(*XML.GetAtribute(layer, "name", TEXT("")));
		LayerFile->WriteString(name_l, BearCore::BearEncoding::UTF16);
		auto data = XML.GetNode(layer, "data");
		auto tile = XML.GetNode(data, "tile");

		while (tile)
		{
			uint32 gid = 0;
			XML.GetAtribute(tile, "gid", TEXT("0")).scanf(TEXT("%u"), &gid);
			if (gid)
			{
				auto item = BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), gid + 1);
				LayerFile->WriteUint32(static_cast<uint32>(item - tile_level.begin()));
				LayerFile->WriteUint32(gid - (*tile_level.begin()));
			}
			else
			{
				LayerFile->WriteUint32(0);
				LayerFile->WriteUint32(0);
			}

			tile = XML.NextNode(tile, "tile");
		}
		count_layer++;
		layer = XML.NextNode(layer, "layer");
	};
	LayerFile->Seek(0);
	LayerFile->WriteUint32(count_layer);
	LayerFile.clear();

	BearCore::BearLog::Printf(TEXT("Size layer[%u] byte"), count_layer*width*height * sizeof(uint32) * 2);

	BearCore::BearLog::Printf(TEXT("Saving... level.collision and level.spawn"));

	CollisionFile->WriteUint32(0);
	uint32 count_collider = 0;
	SpawnFile->WriteUint32(spawn_version);
	SpawnFile->WriteUint32(0);
	uint32 count_spawn = 0;

	auto objectgroup = XML.GetNode(map, "objectgroup");
	if (!objectgroup)return;
	auto object = XML.GetNode(objectgroup, "object");
	while (object)
	{
		bint x_obj = 0, y_obj = 0;
		bsize width_obj = 0, height_obj = 0;
		XML.GetAtribute(object, "x", TEXT("0")).scanf(TEXT("%d"), &x_obj);
		XML.GetAtribute(object, "y", TEXT("0")).scanf(TEXT("%d"), &y_obj);

		XML.GetAtribute(object, "width", TEXT("0")).scanf(TEXT("%u"), &width_obj);
		XML.GetAtribute(object, "height", TEXT("0")).scanf(TEXT("%u"), &height_obj);
		BearCore::BearString type, objname;
		type = XML.GetAtribute(object, "type", TEXT(""));
		BEAR_ASSERT(type.size());
		objname = XML.GetAtribute(object, "name", TEXT(""));
		if (type == TEXT("Collider"))
		{
			if (width_obj&&height_obj)
			{
				CollisionFile->WriteFloat((float)x_obj);	CollisionFile->WriteFloat((float)y_obj); CollisionFile->WriteFloat((float)width_obj); CollisionFile->WriteFloat((float)height_obj);
				count_collider++;
			}
		}
		else
		{
			count_spawn++;
			SpawnFile->WriteString(type,BearCore::BearEncoding::UTF16);
			SpawnFile->WriteString(objname, BearCore::BearEncoding::UTF16);
			SpawnFile->WriteFloat((float)x_obj); SpawnFile->WriteFloat((float)y_obj - (float)height_obj);
			SpawnFile->WriteFloat((float)width_obj); SpawnFile->WriteFloat((float)height_obj);
		}
		object = XML.NextNode(object, "object");
	}
	BearCore::BearLog::Printf(TEXT("Size spawn [%u]"), count_spawn);
	BearCore::BearLog::Printf(TEXT("Size collider [%u]"), count_collider);
	SpawnFile->Seek(4);
	SpawnFile->WriteUint32(count_spawn);
	SpawnFile.clear();
	CollisionFile->Seek(0);
	CollisionFile->WriteUint32(count_collider);
	CollisionFile.clear();
	BearCore::BearLog::Printf(TEXT("Compile level end"));
}
void BearEngine::BearLevel::Destroy()
{
	BEAR_OBJECT_DESTROY(BearLevel);
}
template<class C>
inline bool frustum(C GlobalView,float x, float y, float x1, float y1)
{

	if (x + x1 > GlobalView.x&&x < GlobalView.x1 + GlobalView.x)
		if (y + y1 > GlobalView.y&&y < GlobalView.y1 + GlobalView.y)
			return true;
	return false;
}
void BearEngine::BearLevel::Update(float time)
{
	m_terrain->Update(time);
	for (bsize i = 0; i < Layers.size(); i++)
	{
		bsize x = 0;
		bsize y = 0;
		auto begin = Layers[i]->Layer.begin();
		auto end = Layers[i]->Layer.end();

		auto GlobalView = GRender->GetView();

		while (begin != end)
		{
			if (begin->x&&frustum(GlobalView,static_cast<float>(x*TileWidth), static_cast<float>(y*TileHeight), static_cast<float>(Tilesets[begin->x - 1]->TileWidth), static_cast<float>(Tilesets[begin->x - 1]->TileHeight)))
			{
				auto&sprite = Tilesets[begin->x - 1]->ListTile[begin->y];
				sprite->Position.set(static_cast<float>(x*TileWidth), static_cast<float>(y*TileHeight));
				sprite->Update(time);

			}
			x++;
			if (x == Width) {
				x = 0; y++;
			}
			begin++;
		}
	}
	{
		auto begin = Objects.begin();
		auto end = Objects.end();
		while (begin != end)
		{
			(*begin)->Update(time);
			begin++;
		}
	}
}
void BearEngine::BearLevel::Save(BearCore::BearOutputStream * stream)
{
}
void BearEngine::BearLevel::Load(const BearCore::BearInputStream * stream)
{
}
void BearEngine::BearLevel::EndLoad()
{
}
void BearEngine::BearLevel::SpawnObject(const BearName & Type, const BearName & Name, const BearCore::BearVector4<float>& Rect)
{
	Objects.push_back(GObjectManager->Create<BearObjectLevel>(Type));
	Objects.back()->Name = Name;
	Objects.back()->Rect = Rect;
	Objects.back()->Spawn();
}
void BearEngine::BearLevel::Clear()
{
	{
		auto begin = Tilesets.begin();
		auto end = Tilesets.end();
		while (begin != end)
		{
			auto beginl = (*begin)->ListTile.begin();
			auto endl = (*begin)->ListTile.end();
			while (beginl != endl)
			{
				(*beginl)->Destroy();
				beginl++;
			}
			begin++;
		}
	}
	{
		auto begin = Objects.begin();
		auto end = Objects.end();
		while (begin != end)
		{
			(*begin)->Destroy();
			begin++;
		}
	}
	Tilesets.clear();
	MapTilesetsID.clear();
	Layers.clear();
	MapLayersID.clear();
	Objects.clear();
}
void BearEngine::BearLevel::Load(const bchar * name)
{
	BearCore::FS->SubPath(TEXT("%level%"));
	BearCore::FS->AppendPath(TEXT("%level%"), name, TEXT("%levels%"), 0);
	BearCore::BearLog::Printf(TEXT("Level set [%s]"), name);
	LoadLevel();
	LoadLayer();
	LoadCollision();
	LoadSpawn();
	EndLoad();
}
void BearEngine::BearLevel::LoadLevel()
{
	BearCore::BearLog::Printf(TEXT("Loading... Level"));
	auto LevelFile = BearCore::FS->Read(TEXT("%level%"), TEXT("level"));
	BEAR_ASSERT(LevelFile->ReadUint32() == level_version);
	Width = LevelFile->ReadUint32();
	Height = LevelFile->ReadUint32();
	TileWidth = LevelFile->ReadUint32();
	TileHeight = LevelFile->ReadUint32();
	uint32 count_tileset = LevelFile->ReadUint32();
	BearCore::BearString terrain,t_texture1, t_texture2, t_texture3;
	LevelFile->ReadString(terrain);
	LevelFile->ReadString(t_texture1);	LevelFile->ReadString(t_texture2);	LevelFile->ReadString(t_texture3);
	m_terrain->Load(*terrain,Width*TileWidth,Height*TileHeight,*t_texture1,*t_texture2,*t_texture3);
	BearCore::BearString texture;
	for (uint32 i = 0; i < count_tileset; i++)
	{

		MapTilesetsID.insert(*texture, i);
		texture.clear_no_free();
		LevelFile->ReadString(texture);
		BearLevelTileset*tileset = BearCore::bear_new< BearLevelTileset>();
		tileset->TileWidth = LevelFile->ReadUint32();
		tileset->TileHeight = LevelFile->ReadUint32();
		tileset->Spacing = LevelFile->ReadUint32();
		uint32 count_tile = LevelFile->ReadUint32();;
		for (uint32 a = 0; a < count_tile; a++)
		{
			BearCore::BearVector4<float> UV;
			UV.x = LevelFile->ReadFloat();
			UV.y = LevelFile->ReadFloat();
			UV.x1 = LevelFile->ReadFloat();
			UV.y1 = LevelFile->ReadFloat();
			BearTile*tile = GObjectManager->Create<BearTile>(TEXT("BearEngine::BearTile"));
			tile->SetTexutre(*texture);
			tile->Size.set(static_cast<float>(tileset->TileWidth), static_cast<float>(tileset->TileHeight));
			tile->TextureUV = UV;
			tileset->ListTile.push_back(tile);
		}
		Tilesets.push_back(tileset);
	}
}
void BearEngine::BearLevel::LoadLayer()
{
	BearCore::BearLog::Printf(TEXT("Loading... Level.Layer"));
	auto LayerFile = BearCore::FS->Read(TEXT("%level%"), TEXT("level.layer"));
	uint32 count = LayerFile->ReadUint32();
	for (uint32 i = 0; i < count; i++)
	{
		BearCore::BearString name;
		LayerFile->ReadString(name);
		MapLayersID.insert(*name, i);

		BearLevelLayer*layer = BearCore::bear_new< BearLevelLayer>();
		bsize count_l = Width * Height;
		for (bsize a = 0; a < count_l; a++)
		{
			BearCore::BearVector2<bsize> t;
			t.x = LayerFile->ReadUint32();
			t.y = LayerFile->ReadUint32();
			layer->Layer.push_back(t);
		}
		Layers.push_back(layer);
	}

}
void BearEngine::BearLevel::LoadCollision()
{
	BearCore::BearLog::Printf(TEXT("Loading... Level.Collision"));
	/*
	BearCore::BearLog::Printf(TEXT("Loading... Level.Collision"));
	auto CollisionFile = FS->Read(TEXT("%level%"), TEXT("level.collision"));
	uint32 count = CollisionFile->ReadUint32();
	for (uint32 i = 0; i < count; i++)
	{
		BearCore::BearVector2<float> pos, size;
		pos.x = CollisionFile->ReadFloat();
		pos.y = CollisionFile->ReadFloat();
		size.x = CollisionFile->ReadFloat() / 2;
		size.y = CollisionFile->ReadFloat() / 2;
		colliders.push_back(BearPhysicsCollider::Create(pos, size, size));
	}*/
}
void BearEngine::BearLevel::LoadSpawn()
{
	BearCore::BearLog::Printf(TEXT("Loading... Level.Spawn"));
	auto SpawnFile = BearCore::FS->Read(TEXT("%level%"), TEXT("level.spawn"));
	BEAR_ASSERT(SpawnFile->ReadUint32() == spawn_version);
	uint32 count = SpawnFile->ReadUint32();
	BearCore::BearString  objname,objtype;
	for (uint32 i = 0; i < count; i++)
	{
		
		objname.clear_no_free();
		objtype.clear_no_free();
		SpawnFile->ReadString(objtype);
		SpawnFile->ReadString(objname);
		BearCore::BearVector4<float> rect;
		rect.x = SpawnFile->ReadFloat();
		rect.y = SpawnFile->ReadFloat();
		rect.x1 = SpawnFile->ReadFloat();
		rect.y1 = SpawnFile->ReadFloat();
		Objects.push_back(GObjectManager->Create<BearObjectLevel>(*objtype));
		Objects.back()->Name = *objname;
		Objects.back()->Rect = rect;
		Objects.back()->Spawn();
	}
}
#endif
