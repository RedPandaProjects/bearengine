#pragma once
namespace BearEngine
{
	struct BearVertex
	{
		BearVertex(float x, float y, float z, float u, float v) :position(x,y,z),uv(u,v){}
		BearVertex() {}
		BearCore::BearVector3<float> position;
		BearCore::BearVector2<float> uv;
		inline static bsize getSize(){return sizeof(BearVertex);}
	};
	class BEARENGINE_API BearMeshObject
	{
	public:

		static BearMeshObject*Create();
		
		void destroy();
		inline BearCore::BearVector<BearVertex> & getVertexArray()
		{
			clearVertexBuffer();
			return m_vertex_array;
		}
		inline BearCore::BearVector<uint32> & getIndexArray()
		{
			clearIndexBuffer();
			return m_index_array;
		}
		inline bsize getSizeIndex()
		{
			return m_index_array.size();
		}
		BearVertexBuffer* getVertexBuffer();
		BearIndexBuffer* getIndexBuffer();
	private:
		BearMeshObject();
		~BearMeshObject();
		void clearVertexBuffer();
		void clearIndexBuffer();
		BearCore::BearVector<BearVertex> m_vertex_array;
		BearCore::BearVector<uint32> m_index_array;
		BearVertexBuffer* m_vertex_buffer;
		BearIndexBuffer* m_index_buffer;
	};
}