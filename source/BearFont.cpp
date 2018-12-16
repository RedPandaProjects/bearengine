#include "BearEngine.hpp"
static uint32 version = 0;
BearEngine::BearFont::BearFont() :m_size(0)
{
}

BearEngine::BearFont::BearFont(const bchar*name) :m_size(0)
{
	BearCore::BearLog::Printf(TEXT("Load font [%s]"), name);
	BearCore::BearStringPath texture_name;
	BearCore::BearString::Copy(texture_name, TEXT("fonts_"));
	BearCore::BearString::Contact(texture_name, name);
	m_texture_name = texture_name;
	auto font = BearCore::FS->Read(TEXT("%fonts%"), name, TEXT(".bfi"));
	BEAR_ASSERT(font->ReadUint32() == version);
	m_size = static_cast<bsize>(font->ReadUint32());
	uint32 count = font->ReadUint32();
	for (uint32 i = 0; i < count; i++)
	{
		bchar16 c = font->ReadUint16();
		CharInfo charinfo;
		charinfo.size.x = font->ReadFloat();
		charinfo.size.y = font->ReadFloat();
		charinfo.textureUV.x = font->ReadFloat();
		charinfo.textureUV.y = font->ReadFloat();
		charinfo.textureUV.x1 = font->ReadFloat();
		charinfo.textureUV.y1 = font->ReadFloat();
		charinfo.advance = font->ReadFloat();
		charinfo.position.x = font->ReadFloat();
		charinfo.position.y = font->ReadFloat();
		CharsInfo.insert(c, charinfo);
	}
}

BearEngine::BearFont::~BearFont()
{
}
#ifdef EDITOR
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
void BearEngine::BearFont::Compile(const bchar * name)
{
	BearCore::BearINI ini;
	BearCore::FS->ReadConfig(TEXT("%import%"), name, TEXT(".ltx"), ini, BearCore::BearEncoding::UTF8);
	BearCore::BearLog::Printf(TEXT("Compile Font [%s]"), name);
	BearCore::FS->CreatePath(TEXT("%fonts%"),0);
	auto font_file = BearCore::FS->Write(TEXT("%fonts%"), name, TEXT(".bfi"), 0);
	
	auto &value_file = ini.Key(TEXT("font"), TEXT("file"))[0];
	BearCore::BearMemoryStream font(**BearCore::FS->Read(TEXT("%import%"), *value_file));



	FT_Library library=0;
	FT_Face     face=0;
	BEAR_ASSERT(FT_Init_FreeType(&library) == 0);
	BEAR_ASSERT(FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(font.Begin()), static_cast<FT_Long>(font.Size()), 0, &face) == 0);


	auto value_widht = ini.Key(TEXT("font"), TEXT("widht"))[0];
	uint32 widht = 0;
	value_widht.scanf(TEXT("%u"), &widht);

	auto value_height = ini.Key(TEXT("font"), TEXT("height"))[0];
	uint32 height = 0;
	value_height.scanf(TEXT("%u"), &height);

	auto value_chars = ini.Key(TEXT("font"), TEXT("chars"))[0];
	value_chars.append(TEXT(" "));
	auto chars = BearCore::BearEncoding::ToUTF16(*value_chars);


	auto value_size = ini.Key(TEXT("font"), TEXT("size"))[0];
	uint32 size = 0;
	value_size.scanf(TEXT("%u"), &size);


	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	FT_Set_Char_Size(face, 0, size * 64, widht, height);
	FT_Set_Pixel_Sizes(face, 0, size);;
	bsize chars_size = value_chars.size();

	uint32 x_t = 0, y_t = 0;
	uint32 max_y = 0;
	uint32 size_texture = static_cast<uint32>(BearCore::bear_recommended_size(static_cast<bsize>(sqrtf(static_cast<float>(chars_size*size*size)))));
	BearGraphics::BearImage texture;
	texture.Create(size_texture, size_texture, false, 1, BearGraphics::TPF_R8);
	texture.Fill(BearCore::BearColor::Transparent);
	font_file->WriteUint32(version);
;
	font_file->WriteUint32(static_cast<uint32>(face->size->metrics.height) / static_cast<uint32>(1 << 6));
	font_file->WriteUint32(static_cast<uint32>(chars_size));

	BearCore::BearLog::Printf(TEXT("Char size [%d]"), static_cast<uint32>(chars_size));
	for (bsize i = 0; i < chars_size; i++) {

		bchar16 id = chars[i];
		font_file->WriteUint16(id);
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
		char_img.Create(width_char, height_char, false, 1, BearGraphics::TPF_R8);
		char_img.Fill(BearCore::BearColor::Black);



		for (uint32 y = 0; y < height_char; ++y)
		{
			for (uint32 x = 0; x < width_char; ++x)
			{

				bsize index = static_cast<bsize> (x + y * width_char);
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

		texture.Append(x_t, y_t, char_img, 0, 0);

		bsize x = x_t;
		bsize y = y_t;

		x_t += width_char;
		float advance = static_cast<float>(face->glyph->metrics.horiAdvance) / static_cast<float>(1 << 6);
		float pos_x = static_cast<float>(face->glyph->metrics.horiBearingX) / static_cast<float>(1 << 6);
		float pos_y = static_cast<float>(size) - ((static_cast<float>(face->glyph->metrics.horiBearingY) / static_cast<float>(1 << 6))) -1;
		BEAR_ASSERT(pos_y >= 0);
		font_file->WriteFloat((static_cast<float>(face->glyph->metrics.width) / static_cast<float>(1 << 6)));
		font_file->WriteFloat((static_cast<float>(face->glyph->metrics.height) / static_cast<float>(1 << 6)));
		font_file->WriteFloat(x / static_cast<float>(size_texture));
		font_file->WriteFloat(y / static_cast<float>(size_texture));
		font_file->WriteFloat(width_char / static_cast<float>(size_texture));
		font_file->WriteFloat(height_char / static_cast<float>(size_texture));
		font_file->WriteFloat(advance);
		font_file->WriteFloat(pos_x);
		font_file->WriteFloat(pos_y);
	}

	BearCore::BearLog::Printf(TEXT("Max y [%d]"), static_cast<uint32>(max_y));
	font_file->WriteUint32(max_y);
	BearCore::BearStringPath out_path;
	BearCore::FS->UpdatePath(TEXT("%fonts%"), 0, out_path);
	BearCore::BearString::Contact(out_path, BEAR_PATH);
	BearCore::BearString::Contact(out_path, TEXT("fonts"));
	BearCore::BearString::Contact(out_path, TEXT("_"));
	BearCore::BearString::Contact(out_path, name);
	BearCore::BearString::Contact(out_path, TEXT(".dds"));
	texture.Convert(BearGraphics::TPF_BC4);
	BEAR_ASSERT(texture.SaveToDds(out_path));
	FT_Done_Face(face);
	FT_Done_FreeType(library);
	BearCore::BearLog::Printf(TEXT("Compile font end"));
}
#endif
void BearEngine::BearFont::clear()
{
	m_size = 0;
	CharsInfo.clear();
}

void BearEngine::BearFont::swap(BearFont & right)
{
	m_texture_name.swap(right.m_texture_name);
	BearCore::bear_swap(m_size, right.m_size);
	CharsInfo.swap( right.CharsInfo);
}

void BearEngine::BearFont::copy(const BearFont & right)
{
	m_texture_name = right.m_texture_name;
	m_size = right.m_size;
	CharsInfo = right.CharsInfo;
}

BearEngine::BearFont::BearFont(BearFont && right)
{
	swap(right);
}
BearEngine::BearFont::BearFont(const BearFont & right)
{
	copy(right);
}

BearEngine::BearFont & BearEngine::BearFont::operator=(const BearFont & right)
{
	copy(right);
	return*this;
}

BearEngine::BearFont & BearEngine::BearFont::operator=(BearFont && right)
{
	swap(right);
	return*this;
}
