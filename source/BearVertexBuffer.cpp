#include "BearEngine.hpp"

BearEngine::BearVertexBuffer * BearEngine::BearVertexBuffer::Create()
{
	return BearCore::bear_new< BearVertexBuffer>();
}

BearEngine::BearVertexBuffer::~BearVertexBuffer()
{
	BearCore::bear_delete(get<BearGraphics::BearVertexBufferRef>());
}

BearEngine::BearVertexBuffer::BearVertexBuffer()
{
	get<BearGraphics::BearVertexBufferRef>() = BearCore::bear_new<BearGraphics::BearVertexBufferRef>();
}
