#pragma once
namespace BearEngine
{
	class BearVertexBuffer :public BearResource
	{
	public:
		BEAR_CLASS_NO_COPY(BearVertexBuffer);
		static BearVertexBuffer* Create();
		void destroy();
	private:
		~BearVertexBuffer();
		BearVertexBuffer();
	};
}