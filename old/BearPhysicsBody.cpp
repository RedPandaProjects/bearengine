#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
extern b2World*PhysicsWorld ;
BearEngine::BearPhysicsBody::BearPhysicsBody()
{
	getRef<b2Body>() = 0;
}

void BearEngine::BearPhysicsBody::create(BearPhysicsShape & shape, float x, float y, bool dynamic)
{
	clear();
	b2BodyDef BodyDef;
	BodyDef.position.Set(x, y);
	if (dynamic)
		BodyDef.type = b2_dynamicBody;
	getRef<b2Body>() = PhysicsWorld->CreateBody(&BodyDef);
	if (dynamic)
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = shape.getRef< b2PolygonShape>();
		fixtureDef.density = 1.0f;

		fixtureDef.friction = 0.3f;

		getRef<b2Body>()->CreateFixture(&fixtureDef);
	}
	else
	{
		getRef<b2Body>()->CreateFixture(shape.getRef< b2PolygonShape>(), 0.0f);
	}
}

BearCore::BearVector2<float> BearEngine::BearPhysicsBody::getPosition() const
{
	if (getRef<b2Body>())
	{
		auto pos = getRef<b2Body>()->GetPosition();
		return BearCore::BearVector2<float>(pos.x,pos.y);
	}
	return BearCore::BearVector2<float>();
}


void BearEngine::BearPhysicsBody::clear()
{
	if (getRef<b2Body>())
		PhysicsWorld->DestroyBody(getRef<b2Body>());
	getRef<b2Body>() = 0;
}

BearEngine::BearPhysicsBody::~BearPhysicsBody()
{
	clear();
}
