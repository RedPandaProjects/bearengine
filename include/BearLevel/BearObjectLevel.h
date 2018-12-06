#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearObjectLevel :public BearObject
	{
		BEAR_OBJECT(BearObjectLevel);
	protected:
		BearObjectLevel(const BearName&type,uint32 flags);
		~BearObjectLevel();
	public:
		virtual void Spawn();
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		BearName Name;
		union
		{
			BearCore::BearVector4<float> Rect;
			struct
			{
				BearCore::BearVector2<float> Position;
				BearCore::BearVector2<float> Size;
			};
		};
		float Rotation;
	};
};