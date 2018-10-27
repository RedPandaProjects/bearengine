#pragma once
namespace BearEngine
{
	class BearObject
	{
	public:
		virtual void spawn(float x, float y) = 0;
		virtual void update(float time)=0;
		virtual void destroy() = 0;
	
	};
}