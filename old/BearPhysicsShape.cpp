#include "BearEngine.hpp"
#include "Box2D/Box2D.h"
#define Shape
BearEngine::BearPhysicsShape::BearPhysicsShape()
{
	getRef<b2PolygonShape>() = 0;
}

BearEngine::BearPhysicsShape::~BearPhysicsShape()
{
	clear();
}

void BearEngine::BearPhysicsShape::create(BearVertex * vertex)
{
	clear();

}

void BearEngine::BearPhysicsShape::createAsBox(float x, float y)
{
	clear();
	getRef<b2PolygonShape>() = BearCore::bear_new<b2PolygonShape>();
	getRef<b2PolygonShape>()->SetAsBox(x, y);
}

void BearEngine::BearPhysicsShape::clear()
{
	if (getRef<b2PolygonShape>())
		BearCore::bear_delete(getRef<b2PolygonShape>());
	getRef<b2PolygonShape>() = 0;
}
