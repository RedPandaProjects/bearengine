#include "BearEngine.hpp"

BearEngine::BearVertexBuffer * BearEngine::BearVertexBuffer::Create()
{
	auto type = BearCore::bear_alloc< BearVertexBuffer>(1);
	return new(type)BearVertexBuffer();
}

BearEngine::BearVertexBuffer::~BearVertexBuffer()
{
	BearCore::bear_delete(get<BearGraphics::BearVertexBufferRef>());
}

BearEngine::BearVertexBuffer::BearVertexBuffer()
{
	get<BearGraphics::BearVertexBufferRef>() = BearCore::bear_new<BearGraphics::BearVertexBufferRef>();
}
