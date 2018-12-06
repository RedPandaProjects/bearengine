#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
extern b2World*PhysicsWorld;
BearEngine::BearPhysicsCollider * BearEngine::BearPhysicsCollider::Create(const BearCore::BearVector2<float>&position, const BearFixture & fixture, const BearCore::BearVector2<float>& box, const BearCore::BearVector2<float>&center, bool dynamic)
{
	return new(BearCore::bear_alloc< BearPhysicsCollider>(1))BearPhysicsCollider(position, fixture, box,center, dynamic);
}

BearEngine::BearPhysicsCollider * BearEngine::BearPhysicsCollider::Create(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>& box, const BearCore::BearVector2<float>&center)
{
	return new(BearCore::bear_alloc< BearPhysicsCollider>(1))BearPhysicsCollider(position, box,center);
}

BearEngine::BearPhysicsCollider * BearEngine::BearPhysicsCollider::Create(const BearCore::BearVector2<float>&position, const BearFixture & fixture, const BearCore::BearVector<BearCore::BearVector2<float>>& polygon, const BearCore::BearVector2<float>&center, bool dynamic)
{
	return nullptr;
}

BearEngine::BearPhysicsCollider * BearEngine::BearPhysicsCollider::Create(const BearCore::BearVector2<float>&position, const BearCore::BearVector<BearCore::BearVector2<float>>& polygon, const BearCore::BearVector2<float>&center)
{
	return nullptr;
}

BearCore::BearVector2<float> BearEngine::BearPhysicsCollider::getPosition() const
{
	auto pos = get<b2Body>()->GetPosition();
	return BearCore::BearVector2<float>(pos.x, pos.y);
}

void BearEngine::BearPhysicsCollider::setLinearVelocity(const BearCore::BearVector2<float>& tf)
{
	get<b2Body>()->SetLinearVelocity(b2Vec2(tf.x,tf.y));
}


void BearEngine::BearPhysicsCollider::destroy()
{
	PhysicsWorld->DestroyBody(get<b2Body>());
	this->~BearPhysicsCollider();
	BearCore::bear_free(this);
}


BearEngine::BearPhysicsCollider::~BearPhysicsCollider()
{
	
}

BearEngine::BearPhysicsCollider::BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture & fixture, const BearCore::BearVector2<float>& box, const BearCore::BearVector2<float>&center, bool dynamic)
{
	b2BodyDef bodydef;
	bodydef.position.Set(position.x, position.y);
	bodydef.type = b2_dynamicBody;
	bodydef.fixedRotation = true;
	get<b2Body>() = PhysicsWorld->CreateBody(&bodydef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(box.x, box.y, b2Vec2(center.x, center.y), 0);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &boxShape;
	FixtureDef.density = fixture.density;
	FixtureDef.friction= fixture.friction;
	FixtureDef.restitution = fixture.restitution;
	FixtureDef.isSensor = fixture.sensor;

	get<b2Body>()->CreateFixture(& FixtureDef);

}

BearEngine::BearPhysicsCollider::BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearCore::BearVector2<float>& box, const BearCore::BearVector2<float>&center)
{
	b2BodyDef bodydef;
	bodydef.position.Set(position.x, position.y);
	get<b2Body>() = PhysicsWorld->CreateBody(&bodydef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(box.x , box.y , b2Vec2(center.x, center.y), 0);
	get<b2Body>()->CreateFixture(&boxShape, 1.0f);
	
}

BearEngine::BearPhysicsCollider::BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearFixture & fixture, const BearCore::BearVector<BearCore::BearVector2<float>>& polygon, const BearCore::BearVector2<float>&center, bool dynamic)
{
}

BearEngine::BearPhysicsCollider::BearPhysicsCollider(const BearCore::BearVector2<float>&position, const BearCore::BearVector<BearCore::BearVector2<float>>& polygon, const BearCore::BearVector2<float>&center)
{
}
