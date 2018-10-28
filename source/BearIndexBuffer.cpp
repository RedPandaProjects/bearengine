#include "BearEngine.hpp"

BearEngine::BearIndexBuffer * BearEngine::BearIndexBuffer::Create()
{
	auto type= BearCore::bear_alloc< BearIndexBuffer>(1);
	return new(type)BearIndexBuffer();
}

void BearEngine::BearIndexBuffer::destroy()
{
	BearCore::bear_delete(get<BearGraphics::BearIndexBufferRef>());
	get<BearGraphics::BearIndexBufferRef>() = 0;
	this->~BearIndexBuffer();
	BearCore::bear_free(this);
}

BearEngine::BearIndexBuffer::~BearIndexBuffer()
{

}

BearEngine::BearIndexBuffer::BearIndexBuffer()
{
	get<BearGraphics::BearIndexBufferRef>() = BearCore::bear_new<BearGraphics::BearIndexBufferRef>();
}
