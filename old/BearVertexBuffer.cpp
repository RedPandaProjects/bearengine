#include "BearEngine.hpp"

BearEngine::BearVertexBuffer * BearEngine::BearVertexBuffer::Create()
{
	auto type = BearCore::bear_alloc< BearVertexBuffer>(1);
	return new(type)BearVertexBuffer();
}

void BearEngine::BearVertexBuffer::destroy()
{
	BearCore::bear_delete(get<BearGraphics::BearVertexBufferRef>());
	get<BearGraphics::BearVertexBufferRef>() = 0;
	this->~BearVertexBuffer();
	BearCore::bear_free(this);
}

BearEngine::BearVertexBuffer::~BearVertexBuffer()
{

}

BearEngine::BearVertexBuffer::BearVertexBuffer()
{
	get<BearGraphics::BearVertexBufferRef>() = BearCore::bear_new<BearGraphics::BearVertexBufferRef>();
}
