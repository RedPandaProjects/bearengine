#pragma once
namespace BearEngine
{
	struct BearFixture
	{
		BearFixture():friction(0.3f), restitution(0.0f), density(1), sensor(false){}
		float friction;
		float restitution;
		float density;
		bool sensor;
	};
	
	class BEARENGINE_API BearPhysicsCollider:public BearResource
	{
	public:
		BEAR_CLASS_NO_COPY(BearPhysicsCollider);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearFixture&fixture,const BearCore::BearVector2<float>&box, const BearCore::BearVector2<float>&center,bool dynamic=true);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>&box, const BearCore::BearVector2<float>&center);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, const BearCore::BearVector2<float>&center, bool dynamic = true);
		static BearPhysicsCollider*Create(const BearCore::BearVector2<float>&position, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, const BearCore::BearVector2<float>&center);
		BearCore::BearVector2<float> getPosition()const;
		void setLinearVelocity(const BearCore::BearVector2<float>&tf);
		void destroy();
	
	private:
		~BearPhysicsCollider();
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const BearCore::BearVector2<float>&box, const BearCore::BearVector2<float>&center, bool dynamic = true);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>&box, const BearCore::BearVector2<float>&center);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture&fixture, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, const BearCore::BearVector2<float>&center, bool dynamic = true);
		BearPhysicsCollider(const BearCore::BearVector2<float>&position, const  BearCore::BearVector<BearCore::BearVector2<float>>&polygon, const BearCore::BearVector2<float>&center);
	};
}