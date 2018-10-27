#include "BearEngine.hpp"

BearEngine::BearIndexBuffer * BearEngine::BearIndexBuffer::Create()
{
	auto type= BearCore::bear_alloc< BearIndexBuffer>(1);
	return new(type)BearIndexBuffer();
}

BearEngine::BearIndexBuffer::~BearIndexBuffer()
{
	BearCore::bear_delete(get<BearGraphics::BearIndexBufferRef>());
}

BearEngine::BearIndexBuffer::BearIndexBuffer()
{
	get<BearGraphics::BearIndexBufferRef>() = BearCore::bear_new<BearGraphics::BearIndexBufferRef>();
}
