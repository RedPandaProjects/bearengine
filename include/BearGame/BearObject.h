#pragma once
namespace BearEngine
{
	class BearObject
	{
	public:
		virtual void create(const BearCore::BearVector2<float>&position) = 0;
		virtual void update(float time)=0;
		virtual void destroy() = 0;
	
	};
}