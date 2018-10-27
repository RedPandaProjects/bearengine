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
		static void OnAlpha();
		static void OffAlpha();
		static void SetPixelShader(const BearPixelShaderResource&pixel);
		static void SetVertexShader(const BearVertexShaderResource&vertex);
		static void SetTexture2D(const char*name,const BearTexture2DResource&texture);
		static void DrawMeshObject(BearMeshObject&mesh, BearMaterial*material);
	};
}