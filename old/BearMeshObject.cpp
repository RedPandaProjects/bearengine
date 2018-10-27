#include "BearEngine.hpp"

BearEngine::BearMeshObject::BearMeshObject()
{
}

BearEngine::BearMeshObject::~BearMeshObject()
{
	clear();
}

BearEngine::BearMeshObject::BearMeshObject(BearMeshObject && right)
{
	swap(right);
}

BearEngine::BearMeshObject::BearMeshObject(const BearMeshObject & right)
{
	copy(right);
}

void BearEngine::BearMeshObject::copy(const BearMeshObject & right)
{
	m_index_array=right.m_index_array;
	m_vertex_buffer=right.m_vertex_buffer;
}

void BearEngine::BearMeshObject::swap(BearMeshObject & right)
{
	m_index_array.swap(right.m_index_array);
	m_index_buffer.swap(right.m_index_buffer);
	m_vertex_array.swap(right.m_vertex_array);
	m_vertex_buffer.swap(right.m_vertex_buffer);
}

BearEngine::BearMeshObject & BearEngine::BearMeshObject::operator=(const BearMeshObject & right)
{
	copy(right);
	return *this;
}

BearEngine::BearMeshObject & BearEngine::BearMeshObject::operator=(BearMeshObject && right)
{
	swap(right);
	return *this;
}

void BearEngine::BearMeshObject::clear()
{
	m_index_array.clear();
	m_vertex_array.clear();
	clearVertexBuffer();
	clearIndexBuffer();
	if (!m_vertex_buffer.empty())
	{
		BearCore::bear_delete(m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>());
		m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>() = 0;
	}
	if (!m_index_buffer.empty())
	{
		BearCore::bear_delete(m_index_buffer.get<BearGraphics::BearIndexBufferRef>());
		m_index_buffer.get<BearGraphics::BearIndexBufferRef>() = 0;
	}
}

BearEngine::BearVertexBuffer & BearEngine::BearMeshObject::getVertexBuffer()
{
	if (m_vertex_buffer.empty())m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>() = BearCore::bear_new< BearGraphics::BearVertexBufferRef>();
	if (m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>()->empty())m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>()->create(&m_vertex_array[0], m_vertex_array.size()*BearVertexSize, false);
	return m_vertex_buffer;
}

BearEngine::BearIndexBuffer & BearEngine::BearMeshObject::getIndexBuffer()
{
	if (m_index_buffer.empty())m_index_buffer.get<BearGraphics::BearIndexBufferRef>() = BearCore::bear_new< BearGraphics::BearIndexBufferRef>();
	if (m_index_buffer.get<BearGraphics::BearIndexBufferRef>()->empty())m_index_buffer.get<BearGraphics::BearIndexBufferRef>()->create(&m_index_array[0], m_index_array.size()*BearVertexSize, false);
	return m_index_buffer;
}

void BearEngine::BearMeshObject::clearVertexBuffer()
{
	if (!m_vertex_buffer.empty())m_vertex_buffer.get<BearGraphics::BearVertexBufferRef>()->clear();
}

void BearEngine::BearMeshObject::clearIndexBuffer()
{
	if (!m_index_buffer.empty())m_index_buffer.get<BearGraphics::BearIndexBufferRef>()->clear();
}
