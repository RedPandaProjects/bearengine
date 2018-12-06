#include "BearEngine.hpp"
static uint32 version_anim = 1;
BearEngine::BearAnimateArray2D::BearAnimateArray2D()
{
}

BearEngine::BearAnimateArray2D::BearAnimateArray2D(const bchar * animate)
{
	BearCore::BearLog::Printf(TEXT("Load anim  [%s]"), animate);
	auto stream = BearCore::FS->Read(TEXT("%anims%"), animate, TEXT(".baa"));
	BearCore::BearString name_texture, temp;
	BEAR_ASSERT(stream->ReadUint32() == version_anim);
	stream->ReadString(name_texture);
	m_texture_name = *name_texture;
	uint32 count = stream->ReadUint32();
	for (uint32 i = 0; i < count; i++)
	{
		temp.clear_no_free();
		stream->ReadString(temp);
		Animations.insert(*temp, Animation());
		auto item = Animations.find(BearCore::BearStringConteniar(*temp, false));
		item->second.delay = stream->ReadFloat();
		uint32 count_cuts = stream->ReadUint32();
		for (uint32 a = 0; a < count_cuts; a++)
		{
			Cut ct;
			ct.SpriteSize.x = stream->ReadFloat();
			ct.SpriteSize.y = stream->ReadFloat();
			ct.TextureUV.x = stream->ReadFloat();
			ct.TextureUV.y = stream->ReadFloat();
			ct.TextureUV.x1 = stream->ReadFloat();
			ct.TextureUV.y1 = stream->ReadFloat();
			item->second.cuts.push_back(ct);
		}
	}
	stream.clear();
}

BearEngine::BearAnimateArray2D::~BearAnimateArray2D()
{
}

void BearEngine::BearAnimateArray2D::Compile(const bchar * name)
{
	BearCore::BearXML xml;
	BearCore::BearString out1, out2;
	xml.LoadFromStream(**BearCore::FS->Read(TEXT("%import%"), name, TEXT(".xml")), BearCore::BearEncoding::UTF8, out1, out2);
	BearCore::BearLog::Printf(TEXT("Import animation [%s]"), name);
	auto FileOut = BearCore::FS->Write(TEXT("%anims%"), name, TEXT(".baa"), 0);


	auto sprites = xml.GetNode("sprites");
	BearCore::BearString name_texture = xml.GetAtribute(sprites, "image");
	BEAR_ASSERT(name_texture.size());
	name_texture = BearCore::BearFileManager::GetFileName(*name_texture);
	FileOut->WriteUint32(version_anim);
	FileOut->WriteString(name_texture, BearCore::BearEncoding::UTF16);

	bsize tell_count_anim = FileOut->Tell();
	FileOut->WriteUint32(0);

	auto texture = GResourceManager->GetTexture2D(*name_texture);//::Create(*name_texture);
	uint32 count_anim = 0;
	auto animation = xml.GetNode(sprites, "animation");
	while (animation)
	{
		BearCore::BearString cut_name = xml.GetAtribute(animation, "title");
		BEAR_ASSERT(cut_name.size());

		float delay = 0;
		xml.GetAtribute(animation, "delay", TEXT("0")).scanf(TEXT("%f"), &delay);

		FileOut->WriteString(cut_name, BearCore::BearEncoding::UTF16);
		FileOut->WriteFloat(delay);

		bsize tell_count_cut = FileOut->Tell();
		FileOut->WriteUint32(0);

		auto cut = xml.GetNode(animation, "cut");
		uint32 count_cut = 0;
		while (cut)
		{

			Cut cut_;
			xml.GetAtribute(cut, "x", TEXT("0")).scanf(TEXT("%f"), &cut_.TextureUV.x);
			xml.GetAtribute(cut, "y", TEXT("0")).scanf(TEXT("%f"), &cut_.TextureUV.y);
			xml.GetAtribute(cut, "w", TEXT("0")).scanf(TEXT("%f"), &cut_.TextureUV.x1);
			xml.GetAtribute(cut, "h", TEXT("0")).scanf(TEXT("%f"), &cut_.TextureUV.y1);
			cut_.SpriteSize.set(cut_.TextureUV.x1, cut_.TextureUV.y1);
			cut_.TextureUV.x /= texture->get().GetSize().x;
			cut_.TextureUV.x1 /= texture->get().GetSize().x;
			cut_.TextureUV.y /= texture->get().GetSize().y;
			cut_.TextureUV.y1 /= texture->get().GetSize().y;
			FileOut->WriteFloat(cut_.SpriteSize.x);
			FileOut->WriteFloat(cut_.SpriteSize.y);
			FileOut->WriteFloat(cut_.TextureUV.x);
			FileOut->WriteFloat(cut_.TextureUV.y);
			FileOut->WriteFloat(cut_.TextureUV.x1);
			FileOut->WriteFloat(cut_.TextureUV.y1);
			cut = xml.NextNode(cut, "cut");
			count_cut++;
		}
		bsize tell_temp = FileOut->Tell();
		FileOut->Seek(tell_count_cut);
		FileOut->WriteUint32(count_cut);
		FileOut->Seek(tell_temp);
		animation = xml.NextNode(animation, "animation");
		count_anim++;
	}
	FileOut->Seek(tell_count_anim);
	FileOut->WriteUint32(count_anim);
	FileOut.clear();
	GResourceManager->Destroy(texture);
	xml.Clear();
}
void BearEngine::BearAnimateArray2D::clear()
{
	Animations.clear();
}

void BearEngine::BearAnimateArray2D::swap(BearAnimateArray2D & right)
{
	Animations.swap(right.Animations);
	m_texture_name.swap(right.m_texture_name);
}

void BearEngine::BearAnimateArray2D::copy(const BearAnimateArray2D & right)
{
	Animations=right.Animations;
	m_texture_name=right.m_texture_name;
}

BearEngine::BearAnimateArray2D::BearAnimateArray2D(BearAnimateArray2D && right)
{
	swap(right);
}

BearEngine::BearAnimateArray2D::BearAnimateArray2D(const BearAnimateArray2D & right)
{
	copy(right);
}

BearEngine::BearAnimateArray2D & BearEngine::BearAnimateArray2D::operator=(const BearAnimateArray2D & right)
{
	copy(right);
	return*this;
	// TODO: вставьте здесь оператор return
}

BearEngine::BearAnimateArray2D & BearEngine::BearAnimateArray2D::operator=(BearAnimateArray2D && right)
{
	swap(right);
	return*this;
	// TODO: вставьте здесь оператор return
}
