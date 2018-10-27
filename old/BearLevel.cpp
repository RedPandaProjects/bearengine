#include "BearEngine.hpp"
 BEARENGINE_API BearEngine::BearLevel*BearEngine::CurrentLevel=0;
BearEngine::BearLevel::BearLevel()
{
}
static const bchar*LevelsPath = TEXT("..\\..\\content\\stalker2d\\levels\\");
void BearEngine::BearLevel::load(const bchar * name)
{
	BearCore::BearStringPath path;
	BearCore::BearString::Copy(path, LevelsPath);
	BearCore::BearString::Contact(path, name);
	BearCore::BearString::Contact(path, TEXT("\\level.tmx"));
	BearCore::BearXML XML;
	BearCore::BearString out1, out2;
	BEAR_ASSERT(XML.loadFromFile(path, out1, out2));
	auto map = XML.getNode("map");
	BEAR_ASSERT(map);
	m_width = 0;
	XML.getAtribute(map, "width", TEXT("0")).scanf(TEXT("%u"), &m_width);
	BEAR_ASSERT(m_width);
	m_height = 0;
	XML.getAtribute(map, "height", TEXT("0")).scanf(TEXT("%u"), &m_height);
	BEAR_ASSERT(m_height);
	m_tile_width = 0;
	XML.getAtribute(map, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &m_tile_width);
	BEAR_ASSERT(m_tile_width);
	m_tile_height = 0;
	XML.getAtribute(map, "tileheight", TEXT("0")).scanf(TEXT("%u"), &m_tile_height);
	BEAR_ASSERT(m_tile_height);
	auto tileset = XML.getNode(map, "tileset");
	BearCore::BearVector<bsize> tile_level;
	while (tileset)
	{
		BearLevelTileset *Tileset = BearCore::bear_new< BearLevelTileset>();;
		bsize firstgid = 0, width_texture = 0, height_texture = 0;
		XML.getAtribute(tileset, "firstgid", TEXT("0")).scanf(TEXT("%u"), &firstgid);
		BEAR_ASSERT(firstgid);
		Tileset->spacing = 0;
		XML.getAtribute(tileset, "spacing", TEXT("0")).scanf(TEXT("%u"), &Tileset->spacing);
		Tileset->tile_width = 0;
		XML.getAtribute(tileset, "tilewidth", TEXT("0")).scanf(TEXT("%u"), &Tileset->tile_width);
		BEAR_ASSERT(Tileset->tile_width);
		Tileset->tile_height = 0;
		XML.getAtribute(tileset, "tileheight", TEXT("0")).scanf(TEXT("%u"), &Tileset->tile_height);
		BEAR_ASSERT(Tileset->tile_height);
		auto image = XML.getNode(tileset, "image");
		BEAR_ASSERT(image);

		BearCore::BearString temp, source;
		temp = XML.getAtribute(image, "source", TEXT(""));
		BEAR_ASSERT(temp.size());
		temp.find_with_end(TEXT("/"));
		temp++;
		temp.read_to(TEXT('.'), source);

		XML.getAtribute(image, "width", TEXT("0")).scanf(TEXT("%d"), &width_texture);
		BEAR_ASSERT(width_texture);
		XML.getAtribute(image, "height", TEXT("0")).scanf(TEXT("%d"), &height_texture);
		BEAR_ASSERT(height_texture);

		bsize cout_x = width_texture / (Tileset->tile_width);
		bsize cout_y = height_texture / (Tileset->tile_height);
		for (bsize y = 0; y < cout_y; y++)
			for (bsize x = 0; x < cout_x; x++)
			{
				BearSprite*sprite = BearCore::bear_new< BearSprite>();
				sprite->setTexture(*source);
				sprite->setSize(static_cast<float>(Tileset->tile_width), static_cast<float>(Tileset->tile_height));
				sprite->setUV(static_cast<float>((Tileset->tile_height+ Tileset->spacing)*x) / static_cast<float>(width_texture), static_cast<float>((Tileset->tile_height+ Tileset->spacing)*y) / static_cast<float>(height_texture), static_cast<float>(Tileset->tile_width ) / static_cast<float>(width_texture), static_cast<float>(Tileset->tile_height) / static_cast<float>(height_texture));
				Tileset->layer.push_back(sprite);
			}
		BEAR_ASSERT(BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), firstgid) == tile_level.end());
		tile_level.push_back(firstgid);
		m_tilesets.push_back(Tileset);
		tileset = XML.nextNode(tileset, "tileset");

	}
	auto layer = XML.getNode(map, "layer");
	while (layer)
	{
		BearLevelLayer *Layer = BearCore::bear_new< BearLevelLayer>();;
		auto data = XML.getNode(layer, "data");
		auto tile = XML.getNode(data, "tile");
		while (tile)
		{
			bsize gid = 0;
			XML.getAtribute(tile, "gid", TEXT("0")).scanf(TEXT("%u"), &gid);
			if (gid)
			{
				auto item = BearCore::bear_lower_bound(tile_level.begin(), tile_level.end(), gid +1);

				Layer->layer.push_back(BearCore::BearVector2<bsize>(item - tile_level.begin(), gid - *tile_level.begin()));
			}
			else
			{
				Layer->layer.push_back(BearCore::BearVector2<bsize>(0, 0));
			}
			tile = XML.nextNode(tile, "tile");
		}
		BEAR_ASSERT(Layer->layer.size() == m_width * m_height);
		m_layers.push_back(Layer);
		layer = XML.nextNode(layer, "layer");
	};
	auto objectgroup = XML.getNode(map, "objectgroup");
	if (!objectgroup)return;
	auto object = XML.getNode(objectgroup, "object");
	while (object)
	{
		bsize x_obj = 0, y_obj = 0,width_obj=0,height_obj=0;
		XML.getAtribute(object, "x", TEXT("0")).scanf(TEXT("%d"), &x_obj);
		BEAR_ASSERT(x_obj);
		XML.getAtribute(object, "y", TEXT("0")).scanf(TEXT("%d"), &y_obj);
		BEAR_ASSERT(y_obj);
		XML.getAtribute(object, "width", TEXT("0")).scanf(TEXT("%d"), &width_obj);
		BEAR_ASSERT(width_obj);
		XML.getAtribute(object, "height", TEXT("0")).scanf(TEXT("%d"), &height_obj);
		BEAR_ASSERT(height_obj);
		BearCore::BearString type,objname;
		type = XML.getAtribute(object, "type", TEXT(""));
		BEAR_ASSERT(type.size());
		objname = XML.getAtribute(object, "name", TEXT(""));
		if (objname.size())
		{
			BearObject*obj = GameFactory->createObject(BearObjectType(*BearCore::BearEncoding::ToANSI(*type)));
			obj->setPosition(static_cast<float>(x_obj ), static_cast<float>(y_obj - height_obj));
			m_objects.insert(*objname,obj);
		}
		else
		{
			BearObject*obj = GameFactory->createObject(BearObjectType(*BearCore::BearEncoding::ToANSI( *type)));
			obj->setPosition(static_cast<float>(x_obj), static_cast<float>(y_obj-height_obj));
			m_objects_without_name.push_back(obj);
		}
		object = XML.nextNode(object, "object");
	}
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
			if (begin->x)
			{
				auto&sprite = m_tilesets[begin->x - 1]->layer[begin->y];
				sprite->setPosition(static_cast<float>(x*m_tile_width), static_cast<float>(y*m_tile_height));
				sprite->draw();
			
			}
			x++;
			if (x == m_width) {
				x = 0; y++;
			}
			begin++;
		}
	}
	{
		auto begin = m_objects_without_name.begin();
		auto end = m_objects_without_name.end();
		while (begin != end)
		{
			(*begin)->update(time);
			begin++;
		}
	}
	{
		auto begin = m_objects.begin();
		auto end = m_objects.end();
		while (begin != end)
		{
			(begin->second)->update(time);
			begin++;
		}
	}
}
void BearEngine::BearLevel::clear()
{
}



BearEngine::BearLevel::~BearLevel()
{
}
