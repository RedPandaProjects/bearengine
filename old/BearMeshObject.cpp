#include "BearEngine.hpp"

BearEngine::BearMeshObject::BearMeshObject()
{
	m_vertex_buffer = BearVertexBuffer::Create();
	m_index_buffer = BearIndexBuffer::Create();
}

BearEngine::BearMeshObject * BearEngine::BearMeshObject::Create()
{
	auto type = BearCore::bear_alloc< BearMeshObject>(1);
	return new(type)BearMeshObject();
}

void BearEngine::BearMeshObject::destroy()
{
	m_vertex_buffer->destroy();
	m_index_buffer->destroy();
	this->~BearMeshObject();
	BearCore::bear_free(this);
}

BearEngine::BearMeshObject::~BearMeshObject()
{

}


BearEngine::BearVertexBuffer * BearEngine::BearMeshObject::getVertexBuffer()
{
	if (m_vertex_buffer->get<BearGraphics::BearVertexBufferRef>()->empty())
		m_vertex_buffer->get<BearGraphics::BearVertexBufferRef>()->create(&m_vertex_array[0], m_vertex_array.size()*BearVertex::getSize(), false);
	return m_vertex_buffer;
}

BearEngine::BearIndexBuffer * BearEngine::BearMeshObject::getIndexBuffer()
{
	if (m_index_buffer->get<BearGraphics::BearIndexBufferRef>()->empty())
		m_index_buffer->get<BearGraphics::BearIndexBufferRef>()->create(&m_index_array[0], m_index_array.size()*sizeof(uint32), false);
	return m_index_buffer;
}

void BearEngine::BearMeshObject::clearVertexBuffer()
{
	m_vertex_buffer->get<BearGraphics::BearVertexBufferRef>()->clear();
}

void BearEngine::BearMeshObject::clearIndexBuffer()
{
	m_index_buffer->get<BearGraphics::BearIndexBufferRef>()->clear();
}
