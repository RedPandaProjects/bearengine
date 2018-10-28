#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
b2World*PhysicsWorld = 0;
void BearEngine::BearPhysicsWorld::Initialize()
{
	PhysicsWorld = BearCore::bear_new<b2World>(b2Vec2(0,50));

}

void BearEngine::BearPhysicsWorld::Destory()
{
	BearCore::bear_free(PhysicsWorld);
}

void BearEngine::BearPhysicsWorld::Update(float time)
{
	static int32 velocityIterations = 6;
	static int32 positionIterations = 2;
	PhysicsWorld->Step(time, velocityIterations, positionIterations);
}
