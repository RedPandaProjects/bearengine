#include "BearEngine.hpp"
#ifdef EDITOR
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
static uint32 version = 0;
extern BearCore::BearFileSystem *FS;
extern BearCore::BearMap<BearCore::BearStringConteniar, BearEngine::BearMultiResource<BearEngine::BearFont>>*FontMap;
void BearEngine::BearFont::Compile(const bchar * name)
{
	BearCore::BearINI ini;
	FS->readConfig(TEXT("%import%"), name, TEXT(".ltx"), ini, BearCore::BearEncoding::UTF8);
	BearCore::BearDebug::Printf(TEXT("Import Font [%s]"), name);
	auto font_file = FS->write(TEXT("%fonts%"),name,TEXT(".bfi"),0);

	auto item =ini.sections.find(BearCore::BearStringConteniar(TEXT("font"), false));
	BEAR_ASSERT(item != ini.sections.end());
	auto value_file = item->second.find(BearCore::BearStringConteniar(TEXT("file"), false));
	BEAR_ASSERT(value_file != item->second.end());
	BearCore::BearMemoryStream font(**FS->read(TEXT("%import%"), *value_file->second));



	FT_Library library;
	FT_Face     face;
	BEAR_ASSERT(FT_Init_FreeType(&library)==0);
	BEAR_ASSERT(FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(font.begin()), static_cast<FT_Long>(font.size()), 0, &face) == 0);


	auto value_widht = item->second.find(BearCore::BearStringConteniar(TEXT("widht"), false));
	BEAR_ASSERT(value_widht != item->second.end());
	uint32 widht=0;
	value_widht->second.scanf(TEXT("%u"), &widht);

	auto value_height= item->second.find(BearCore::BearStringConteniar(TEXT("height"), false));
	BEAR_ASSERT(value_height != item->second.end());
	uint32 height = 0;
	value_height->second.scanf(TEXT("%u"), &height);

	auto value_chars = item->second.find(BearCore::BearStringConteniar(TEXT("chars"), false));
	BEAR_ASSERT(value_chars != item->second.end());
	value_chars->second.append(TEXT(" "));
	auto chars = BearCore::BearEncoding::ToUTF16(*value_chars->second);


	auto value_size = item->second.find(BearCore::BearStringConteniar(TEXT("size"), false));
	BEAR_ASSERT(value_size != item->second.end());
	uint32 size = 0;
	value_size->second.scanf(TEXT("%u"), &size);


	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	FT_Set_Char_Size(face, 0, size * 64, widht, height);
	FT_Set_Pixel_Sizes(face, 0, size);;
	bsize chars_size = value_chars->second.size();

	uint32 x_t = 0, y_t = 0;
	uint32 max_y = 0;
	uint32 size_texture = static_cast<uint32>(BearCore::bear_recommended_size(static_cast<bsize>(sqrtf(static_cast<float>(chars_size*size*size)))));
	BearGraphics::BearImage texture;
	texture.create(size_texture, size_texture, false, 1, BearGraphics::TPF_R8);
	texture.fill(BearCore::BearColor::Transparent);
	font_file->writeUint32(version);
	font_file->writeUint32(size);
	font_file->writeUint32(static_cast<uint32>(chars_size));
	for (bsize i = 0; i < chars_size; i++) {

		bchar16 id = chars[i];
		font_file->writeUint16(id);
		BEAR_ASSERT(id != L'\r' && id != L'\n' && id != L'	');
		FT_Load_Char(face, id, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT);
		FT_Glyph glyphDesc;
		FT_Get_Glyph(face->glyph, &glyphDesc);
		FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(glyphDesc)->bitmap;
		unsigned char *data = bitmap.buffer;
		uint32 width_char = bitmap.width;
		uint32 height_char = bitmap.rows;

		BearGraphics::BearImage char_img;
		char_img.create(width_char, height_char, false, 1, BearGraphics::TPF_R8);
		char_img.fill(BearCore::BearColor::Black);



		for (uint32 y = 0; y < height_char; ++y)
		{
			for (uint32 x = 0; x < width_char; ++x)
			{

				bsize index =static_cast<bsize> (x + y * width_char);
				((uint8*)*char_img)[index] = data[x];
			}
			data += bitmap.pitch;
		}

		max_y = BearCore::bear_max(height_char, max_y);
		if (x_t + width_char > size_texture)
		{
			x_t = 0; y_t += max_y;
			max_y = 0;
		}

		texture.append(x_t, y_t, char_img, 0, 0);

		bsize x = x_t;
		bsize y = y_t;

		x_t += width_char;
		float advance = static_cast<float>(face->glyph->metrics.horiAdvance) / static_cast<float>(1 << 6);
		float pos_x = static_cast<float>(face->glyph->metrics.horiBearingX) / static_cast<float>(1 << 6) ;
		float pos_y = static_cast<float>(size)- ((static_cast<float>(face->glyph->metrics.horiBearingY) / static_cast<float>(1 << 6)));
		font_file->writeFloat(static_cast<float>(width_char));
		font_file->writeFloat(static_cast<float>(height_char));
		font_file->writeFloat(x / static_cast<float>(size_texture));
		font_file->writeFloat(y/ static_cast<float>(size_texture));
		font_file->writeFloat(width_char / static_cast<float>(size_texture));
		font_file->writeFloat(height_char / static_cast<float>(size_texture));
		font_file->writeFloat(advance);
		font_file->writeFloat(pos_x);
		font_file->writeFloat(pos_y);
	}
	font_file->writeUint32(max_y);
	BearCore::BearStringPath out_path;
	FS->updatePath(TEXT("%fonts%"), 0, out_path);
	BearCore::BearString::Contact(out_path, BEAR_PATH);
	BearCore::BearString::Contact(out_path, TEXT("fonts"));
	BearCore::BearString::Contact(out_path, TEXT("_"));
	BearCore::BearString::Contact(out_path, name);
	BearCore::BearString::Contact(out_path, TEXT(".dds"));
	texture.convert(BearGraphics::TPF_BC4);
	BEAR_ASSERT(texture.saveToDds(out_path));
	FT_Done_Face(face);
	FT_Done_FreeType(library);

}
BearEngine::BearFont * BearEngine::BearFont::Create(const bchar * name)
{
	auto item = FontMap->find(BearCore::BearStringConteniar::BearStringConteniar(name, false));
	if (item == FontMap->end())
	{
		BearCore::BearDebug::Printf(TEXT("Load font [%s]"), name);
		auto result = BearCore::bear_alloc< BearFont>(1);
		new(result)BearFont(name);
		BearMultiResource<BearFont> obj;
		obj.set(result);
		BearCore::BearString::Copy(obj.get()->get_name(), 64, name);
		FontMap->insert(name, obj);
		return result;
	}
	else
	{
		item->second++;
		return   item->second.get();
	}
}
#endif

void BearEngine::BearFont::destroy()
{

	if (CharsInfo.empty())return;

	auto item = FontMap->find(BearCore::BearStringConteniar::BearStringConteniar(get_name(), false));
	BEAR_ASSERT(item != FontMap->end());
	item->second--;
	if (item->second.empty())
	{
		m_texture->destroy();
		CharsInfo.clear();
		FontMap->erase(item);
		BearCore::BearDebug::Printf(TEXT("Unload font [%s]"), get_name());
		this->~BearFont();
		BearCore::bear_free(this);
	}
	
}
BearEngine::BearFont::~BearFont()
{
}
BearEngine::BearFont::BearFont(const bchar * name)
{
	BearCore::BearStringPath texture_name;
	BearCore::BearString::Copy(texture_name, TEXT("fonts_"));
	BearCore::BearString::Contact(texture_name, name);
	m_texture = BearTexture2D::Create(texture_name);
	auto font = FS->read(TEXT("%fonts%"), name,TEXT(".bfi"));
	BEAR_ASSERT(font->readUint32() == version);
	m_size = static_cast<bsize>(font->readUint32());
	uint32 count = font->readUint32();
	for (uint32 i = 0; i < count; i++)
	{
		bchar16 c = font->readUint16();
		CharInfo charinfo;
		charinfo.size.x = font->readFloat();
		charinfo.size.y = font->readFloat();
		charinfo.textureUV.x = font->readFloat();
		charinfo.textureUV.y = font->readFloat();
		charinfo.textureUV.x1 = font->readFloat();
		charinfo.textureUV.y1 = font->readFloat();
		charinfo.advance = font->readFloat();
		charinfo.position.x = font->readFloat();
		charinfo.position.y = font->readFloat();
		CharsInfo.insert(c, charinfo);
	}
	//m_max_y = static_cast<bsize>(font->readUint32());
}
