#include "BearEngine.hpp"
extern  BearEngine::BearMeshObject *Rect2DMesh;
extern   BearCore::BearMatrix Othro;
static uint32 version_anim = 1;
BearEngine::BearSpriteAnimated * BearEngine::BearSpriteAnimated::Create(const bchar * anim)
{
	auto type = BearCore::bear_alloc< BearSpriteAnimated>(1);
	return new(type)BearSpriteAnimated(anim);
}
extern BearCore::BearFileSystem *FS;
#ifdef EDITOR
void BearEngine::BearSpriteAnimated::Compile(const bchar * name)
{
	BearCore::BearXML xml;
	BearCore::BearString out1, out2;
	xml.loadFromStream(**FS->read(TEXT("%import%"), name,TEXT(".xml")), BearCore::BearEncoding::UTF8, out1, out2);
	BearCore::BearDebug::Printf(TEXT("Import animation [%s]"), name);
	auto FileOut = FS->write(TEXT("%anims%"), name, TEXT(".baa"), 0);
	

	auto sprites = xml.getNode("sprites");
	BearCore::BearString name_texture = xml.getAtribute(sprites, "image");
	BEAR_ASSERT(name_texture.size());
	name_texture = BearCore::BearFileManager::GetFileName(*name_texture);
	FileOut->writeUint32(version_anim);
	FileOut->writeString(name_texture, BearCore::BearEncoding::UTF16);

	bsize tell_count_anim = FileOut->tell();
	FileOut->writeUint32(0);

	auto textures = BearTexture2D::Create(*name_texture);
	uint32 count_anim= 0;
	auto animation = xml.getNode(sprites, "animation");
	while (animation)
	{
		BearCore::BearString cut_name = xml.getAtribute(animation, "title");
		BEAR_ASSERT(cut_name.size());
		
		float delay = 0;
		xml.getAtribute(animation, "delay", TEXT("0")).scanf(TEXT("%f"), &delay);

		FileOut->writeString(cut_name, BearCore::BearEncoding::UTF16);
		FileOut->writeFloat(delay);

		bsize tell_count_cut = FileOut->tell();
		FileOut->writeUint32(0);

		auto cut = xml.getNode(animation, "cut");
		uint32 count_cut = 0;
		while (cut)
		{
			
			Cut cut_;
			xml.getAtribute(cut, "x", TEXT("0")).scanf(TEXT("%f"), &cut_.texture_uv.x);
			xml.getAtribute(cut, "y", TEXT("0")).scanf(TEXT("%f"), &cut_.texture_uv.y);
			xml.getAtribute(cut, "w", TEXT("0")).scanf(TEXT("%f"), &cut_.texture_uv.x1);
			xml.getAtribute(cut, "h", TEXT("0")).scanf(TEXT("%f"), &cut_.texture_uv.y1);
			cut_.sprite_size.set(cut_.texture_uv.x1, cut_.texture_uv.y1);
			cut_.texture_uv.x /= textures->getSize().x;
			cut_.texture_uv.x1 /= textures->getSize().x;
			cut_.texture_uv.y /= textures->getSize().y;
			cut_.texture_uv.y1 /= textures->getSize().y;
			FileOut->writeFloat(cut_.sprite_size.x);
			FileOut->writeFloat(cut_.sprite_size.y);
			FileOut->writeFloat(cut_.texture_uv.x);
			FileOut->writeFloat(cut_.texture_uv.y);
			FileOut->writeFloat(cut_.texture_uv.x1);
			FileOut->writeFloat(cut_.texture_uv.y1);
			cut = xml.nextNode(cut, "cut");
			count_cut++;
		}
		bsize tell_temp = FileOut->tell();
		FileOut->seek(tell_count_cut);
		FileOut->writeUint32(count_cut);
		FileOut->seek(tell_temp);
		animation = xml.nextNode(animation, "animation");
		count_anim++;
	}
	FileOut->seek(tell_count_anim);
	FileOut->writeUint32(count_anim);
	FileOut.clear();
	textures->destroy();
	xml.clear();
}
#endif
void BearEngine::BearSpriteAnimated::destroy()
{
	m_material->destroy();
	this->~BearSpriteAnimated();
	BearCore::bear_free(this);
}

void BearEngine::BearSpriteAnimated::draw(float time)
{
	if (m_current_animation == m_animations.end())return;
	if (m_current_time > m_current_animation->second.delay&&m_current_cut!= m_current_animation->second.cuts.end())
	{
		m_current_cut++;
		m_current_time = 0;
	}
	else
	{
		m_current_time += time*1000;
	}
	if (m_current_cut == m_current_animation->second.cuts.end())
	{
		m_current_cut = m_current_animation->second.cuts.begin();
		m_current_time = 0;
	}
	static_cast<BearMaterialSpriteAlpha*>(m_material)->TextureUV = m_current_cut->texture_uv;
	if (m_update)update();
	BearRender::DrawMeshObject(Rect2DMesh, m_material);
}


void BearEngine::BearSpriteAnimated::setAnimation(const bchar * name)
{
	m_current_animation = m_animations.find(name);
	if(m_current_animation != m_animations.end())
	m_current_cut = m_current_animation->second.cuts.end();

}

BearEngine::BearSpriteAnimated::~BearSpriteAnimated()
{
}



BearEngine::BearSpriteAnimated::BearSpriteAnimated(const bchar * animate)
{
	BearCore::BearDebug::Printf(TEXT("Load anim  [%s]"), animate);
	auto stream = FS->read(TEXT("%anims%"), animate, TEXT(".baa"));
	BearCore::BearString name_texture,temp;
	BEAR_ASSERT(stream->readUint32() == version_anim);
	stream->readString(name_texture);
	uint32 count = stream->readUint32();
	for (uint32 i = 0; i < count; i++)
	{
		temp.clear_no_free();
		stream->readString(temp);
		m_animations.insert(*temp, Animation());
		auto item = m_animations.find(BearCore::BearStringConteniar(*temp, false));
		item->second.delay = stream->readFloat();
		uint32 count_cuts = stream->readUint32();
		for (uint32 a = 0; a < count_cuts; a++)
		{
			Cut ct;
			ct.sprite_size.x = stream->readFloat();
			ct.sprite_size.y = stream->readFloat();
			ct.texture_uv.x = stream->readFloat();
			ct.texture_uv.y = stream->readFloat();
			ct.texture_uv.x1 = stream->readFloat();
			ct.texture_uv.y1 = stream->readFloat();
			item->second.cuts.push_back(ct);
		}
	}
	stream.clear();

	BearMaterialSpriteAlpha* mat = BearMaterialSpriteAlpha::Create();
	mat->Texture = BearTexture2D::Create(*name_texture);
	mat->Matrix.buildIdentity();
	mat->TextureUV.set(0, 0, 1, 1);
	m_material = mat;

	m_current_animation = m_animations.end();
	m_rotation = 0;
	m_size.set(100, 100);
	m_position.set(0, 0);
}

void BearEngine::BearSpriteAnimated::update()
{
	m_update = false;
	BearCore::BearMatrix Object;
	Object.buildIdentity();

	Object = Object * BearCore::BearMatrix().scale(m_current_cut->sprite_size.x, m_current_cut->sprite_size.y, 0);
	Object = Object * BearCore::BearMatrix().rotateZ(m_rotation);
	Object = Object * BearCore::BearMatrix().translation(m_position.x+( (m_size.x-m_current_cut->sprite_size.x)/2), m_position.y+(m_size.y- m_current_cut->sprite_size.y), 0);


	m_material->Matrix = Object * Othro;
}
