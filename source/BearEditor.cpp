#include "BearEngine.hpp"

BearEngine::BearEditor::BearEditor(const BearName & type):BearEngine(type)
{
}

BearEngine::BearEditor::~BearEditor()
{
}

void BearEngine::BearEditor::Loop()
{
}

void BearEngine::BearEditor::Initialize( bchar ** V, int32 C)
{
	for (int32 i = 0; i < C; i++)
	{
		if (BearCore::BearString::Compare(V[i], TEXT("-import"))==0&&i+2<C)
		{
			i++;
			if (BearCore::BearString::Compare(V[i], TEXT("textures")) == 0)
			{
				i++;
				CompileTextures(V[i]);
				return;
			}
			else if (BearCore::BearString::Compare(V[i], TEXT("font")) == 0)
			{
				i++;
				BearFont::Compile(V[i]);
				return;
			}
			else if (BearCore::BearString::Compare(V[i], TEXT("animate")) == 0)
			{
				i++;
				BearAnimateArray2D::Compile(V[i]);
				return;
			}
			else if (BearCore::BearString::Compare(V[i], TEXT("level")) == 0)
			{
				i++;
				BearLevel::Compile(V[i]);
				return;
			}
		}
	}
}

void BearEngine::BearEditor::Destroy()
{
	BEAR_OBJECT_DESTROY(BearEditor)
}

void BearEngine::BearEditor::CompileTextures(const bchar * type)
{
	BearCore::BearLog::Printf(TEXT("--------------------------Start Texture Import--------------------------"));
	BearGraphics::BearTexturePixelFormat format = BearGraphics::TPF_R8G8B8A8;
	if (BearCore::BearString::Compare(type, TEXT("dxt1"))==0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_DXT_1;
	}else if (BearCore::BearString::Compare(type, TEXT("dxt1a")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_DXT_1_alpha;
	}
	else if (BearCore::BearString::Compare(type, TEXT("dxt3")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_DXT_3;
	}
	else if (BearCore::BearString::Compare(type, TEXT("dxt5")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_DXT_5;
	}
	else if (BearCore::BearString::Compare(type, TEXT("bc4")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_BC4;
	}
	else if (BearCore::BearString::Compare(type, TEXT("bc5")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_BC5;
	}
	else if (BearCore::BearString::Compare(type, TEXT("rgba")) == 0)
	{
		BearCore::BearLog::Printf(TEXT("Format:%s"), type);
		format = BearGraphics::TPF_R8G8B8A8;
	}
	else
	{
		BearCore::BearLog::Printf(TEXT("Format Not Support:%s"),type);
		BearCore::BearLog::Printf(TEXT("Format:RGBA"));
	}
	BearCore::BearVector<BearCore::BearString> textures;
	BearCore::FS->GetFiles(textures, TEXT("%import%"), TEXT("*.tga"));
	BearCore::FS->GetFiles(textures, TEXT("%import%"), TEXT("*.png"));
	BearCore::FS->GetFiles(textures, TEXT("%import%"), TEXT("*.jpg"));
	BearCore::BearLog::Printf(TEXT("Count:%u"), uint32(textures.size()));
	auto begin = textures.begin();
	auto end = textures.end();
	while (begin != end)
	{
		CompileTexture(**begin, format);
		BearCore::BearStringPath file, new_file;
		BearCore::FS->Update(TEXT("%import%"), **begin, file);
		BearCore::BearString::Copy(new_file, file);
		BearCore::BearString::Contact(new_file, TEXT(".old"));
		BearCore::BearFileManager::FileMove(file, new_file);
		begin++;
	}
	BearCore::BearLog::Printf(TEXT("------------------------------------------------------------------------"));
}

void BearEngine::BearEditor::CompileTexture(const bchar * file, BearGraphics::BearTexturePixelFormat format)
{
	BearGraphics::BearImage img;
	BearCore::BearLog::Printf(TEXT("Import texture [%s]"), file);
	img.LoadFromStream(**BearCore::FS->Read(TEXT("%import%"), file));
	img.GenerateMipmap();
	img.Convert(format);
	BearCore::BearStringPath out_path, floder_name;
	BearCore::FS->UpdatePath(TEXT("%textures%"), 0, out_path);
	BearCore::BearString name_file = BearCore::BearFileManager::GetFileName(file);
	file = *name_file;
	file = BearCore::BearString::ReadTo(file, TEXT("_"), floder_name);
	if (!file[0])
	{
		file = floder_name;

	}
	else
	{
		BearCore::BearString::Contact(out_path, BEAR_PATH);
		BearCore::BearString::Contact(out_path, floder_name);
		if (!BearCore::BearFileManager::DirectoryExists(out_path))
			BEAR_ASSERT(BearCore::BearFileManager::DirectoryCreate(out_path));
	}
	BearCore::BearString::Contact(out_path, BEAR_PATH);
	BearCore::BearString::Contact(out_path, floder_name);
	BearCore::BearString::Contact(out_path, TEXT("_"));
	BearCore::BearString::Contact(out_path, file);
	BearCore::BearString::Contact(out_path, TEXT(".dds"));
	BEAR_ASSERT(img.SaveToDds(out_path));
}
