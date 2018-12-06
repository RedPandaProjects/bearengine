#include "BearEngine.hpp"
extern BearCore::BearFileSystem *FS;
extern bool bRecompileShader;
void BearEngine::BearShaderManager::Initialize()
{
	FS->appendPath(TEXT("%shaders_cur%"), BearDevice::GetNameGraphics(), TEXT("%shaders%"), 0);
	FS->appendPath(TEXT("%app_shaders_cur%"), BearDevice::GetNameGraphics(), TEXT("%app_shaders%"), 0);
	FS->createPath(TEXT("%app_shaders_cur%"),0);
}

void BearEngine::BearShaderManager::CompilePixelShader(const bchar * name)
{

	if (!FS->existFile(TEXT("%app_shaders_cur%"), name, TEXT(".ps.bin")) || bRecompileShader)
	{
		BearCore::BearDebug::Printf(TEXT("Compile pixel [%s]"), name);
		BearGraphics::BearShaderPixelCompilerRef compile;
		BearCore::BearString out_error;
		BEAR_ASSERT(compile.compileFromStream(**FS->read(TEXT("%shaders_cur%"), name, TEXT(".ps")), BearCore::BearEncoding::UTF8, out_error));

		BearCore::BearStringPath file;
		FS->updatePath(TEXT("%app_shaders_cur%"), 0, file);
		BearCore::BearString::Contact(file,BEAR_PATH);
		BearCore::BearString::Contact(file, name);
		BearCore::BearString::Contact(file,TEXT(".ps.bin"));
		compile.saveToFile(file);
	}
	
}

void BearEngine::BearShaderManager::CompileVertexShader(const bchar * name)
{
	if (!FS->existFile(TEXT("%app_shaders_cur%"), name, TEXT(".vs.bin")) || bRecompileShader)
	{
		BearCore::BearDebug::Printf(TEXT("Compile vertex [%s]"), name);
		BearGraphics::BearShaderVertexCompilerRef compile;
		BearCore::BearString out_error;
		compile.compileFromStream(**FS->read(TEXT("%shaders_cur%"), name, TEXT(".vs")), BearCore::BearEncoding::UTF8, out_error);

		BearCore::BearStringPath file;
		FS->updatePath(TEXT("%app_shaders_cur%"), 0, file);
		BearCore::BearString::Contact(file, BEAR_PATH);
		BearCore::BearString::Contact(file, name);
		BearCore::BearString::Contact(file, TEXT(".vs.bin"));
		compile.saveToFile(file);
	}
}

void BearEngine::BearShaderManager::Destroy()
{
}


