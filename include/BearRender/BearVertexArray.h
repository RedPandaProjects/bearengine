#pragma once
namespace BearEngine
{
	class BearVertexArray:BearCore::BearVector<BearVertex>
	{
	public:
		inline void push_plane(const BearCore::BearVector4<float>&rect, const BearCore::BearVector4<float>&texture_uv)
		{
			BearVertex vertex;

			vertex.Position.set(rect.x, rect.y + rect.y1);
			vertex.TextureUV.set(texture_uv.x, texture_uv.y + texture_uv.y1);

			push_back(vertex);

			vertex.Position.set(rect.x + rect.x1, rect.y );
			vertex.TextureUV.set(texture_uv.x + texture_uv.x1, texture_uv.y );

			push_back(vertex);

			vertex.Position.set(rect.x, rect.y );
			vertex.TextureUV.set(texture_uv.x , texture_uv.y);

			push_back(vertex);

			vertex.Position.set(rect.x + rect.x1, rect.y + rect.y1);
			vertex.TextureUV.set(texture_uv.x + texture_uv.x1, texture_uv.y + texture_uv.y1);

			push_back(vertex);
		}
	};
}