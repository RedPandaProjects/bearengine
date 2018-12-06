#pragma once
namespace BearEngine
{
	struct BearVertex
	{
		BearCore::BearVector2<float> Position;
		BearCore::BearFVector2 TextureUV;
		static inline bsize Size() { return sizeof(BearVertex); }
	};
}