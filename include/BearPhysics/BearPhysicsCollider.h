#pragma once
namespace BearEngine
{
	struct BearFixture
	{
		BearFixture():friction(0), restitution(0), density(0), sensor(0){}
		float friction;
		float restitution;
		float density;
		bool sensor;
	};
	
	class BEARENGINE_API BearPhysicsCollider:public BearResource
	{
	public:
		BEAR_CLASS_NO_COPY(BearPhysicsCollider);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearFixture&fixture,const BearCore::BearVector2<float>&box,bool dynamic=true);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>&box);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, bool dynamic = true);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon);
		BearCore::BearVector2<float> getPosition()const;
		void setPosition(const BearCore::BearVector2<float>&tf);
		void destroy();
	
	private:
		~BearPhysicsCollider();
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const BearCore::BearVector2<float>&box, bool dynamic = true);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>&box);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, bool dynamic = true);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon);
	};
}