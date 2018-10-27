#include "BearEngine.hpp"

BearEngine::BearIndexBuffer * BearEngine::BearIndexBuffer::Create()
{
	return BearCore::bear_new< BearIndexBuffer>();
}

BearEngine::BearIndexBuffer::~BearIndexBuffer()
{
	BearCore::bear_delete(get<BearGraphics::BearIndexBufferRef>());
}

BearEngine::BearIndexBuffer::BearIndexBuffer()
{
	get<BearGraphics::BearIndexBufferRef>() = BearCore::bear_new<BearGraphics::BearIndexBufferRef>();
}
