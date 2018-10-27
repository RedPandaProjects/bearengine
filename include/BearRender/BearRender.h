#pragma once
namespace BearEngine
{
	class BearRender
	{
		BEAR_CLASS_STATIC(BearRender);
	public:
		static void Initialize();
		static void Clear();
		static void Swap();
		static void Destory();
		static void AlphaOn();
		static void AlphaOff();
		static void Set(const BearPixelShader*pixel);
		static void Set(const BearVertexShader*vertex);
		static void SetPS(const char*name,const BearTexture2D*texture);
		static void SetVS(const char*name, const BearTexture2D*texture);
		static void DrawMeshObject(BearMeshObject*mesh,BearMaterialInstance*material);
	};
}