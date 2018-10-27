#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearPhysicsBody
	{
	public:
		BEAR_CLASS_NO_COPY(BearPhysicsBody);
		BearPhysicsBody(float x,float y,float hx,float hy,bool dynamic=false);
		BearCore::BearVector2<float> getPosition()const;
		void clear();
		~BearPhysicsBody();
	private:
	};
}