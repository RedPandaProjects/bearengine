#pragma once
namespace BearEngine
{
	class BEARENGINE_API Bear2DPlane :public BearObject
	{
		BEAR_OBJECT(Bear2DPlane);
		Bear2DPlane(const BearName&type);
		~Bear2DPlane();
	public:
		virtual void Destroy();
		virtual void Update(BearVertex vertex[4]) ;
	private:
		virtual void Update( float time)override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;
		BearGraphics::BearVertexBufferRef VertexBuffer;
		BearGraphics::BearIndexBufferRef IndexBuffer;
	};
	extern BEARENGINE_API Bear2DPlane*G2DPlane;
}