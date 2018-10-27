#pragma once
namespace BearEngine
{
	class BearVertexShader :public BearResourceWithName
	{
		BEAR_CLASS_NO_COPY(BearVertexShader);
		static BearVertexShader* Create(const bchar*name);
		~BearVertexShader();
	private:
		BearVertexShader(const bchar*name);
	};
}