#pragma once
namespace BearEngine
{
	class BearShaderManager
	{
		BEAR_CLASS_STATIC(BearShaderManager);
	public:
		static void Initialize();
		static void CompilePixelShader(const bchar*name);
		static void CompileVertexShader(const bchar*name);
		static void Destroy();
	};
}