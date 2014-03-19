#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "Dispatcher.h"
#include "MultiBody.h"
#include "MultiBodyConstraint.h"
#include "MultiBodyConstraintSolver.h"
#include "MultiBodyDynamicsWorld.h"

#define Native static_cast<btMultiBodyDynamicsWorld*>(_native)

MultiBodyDynamicsWorld::MultiBodyDynamicsWorld(btMultiBodyDynamicsWorld* native)
	: DiscreteDynamicsWorld(native)
{
}

MultiBodyDynamicsWorld::MultiBodyDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
	MultiBodyConstraintSolver^ constraintSolver, CollisionConfiguration^ collisionConfiguration)
	: DiscreteDynamicsWorld(new btMultiBodyDynamicsWorld(dispatcher->_native, pairCache->_native,
		(btMultiBodyConstraintSolver*)constraintSolver->_native, collisionConfiguration->_native))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void MultiBodyDynamicsWorld::AddMultiBody(MultiBody^ body, short group, short mask)
{
	Native->addMultiBody(body->_native, group, mask);
}

void MultiBodyDynamicsWorld::AddMultiBody(MultiBody^ body, short group)
{
	Native->addMultiBody(body->_native, group);
}

void MultiBodyDynamicsWorld::AddMultiBody(MultiBody^ body)
{
	Native->addMultiBody(body->_native);
}

void MultiBodyDynamicsWorld::AddMultiBodyConstraint(MultiBodyConstraint^ constraint)
{
	Native->addMultiBodyConstraint(constraint->_native);
}

void MultiBodyDynamicsWorld::RemoveMultiBody(MultiBody^ body)
{
	Native->removeMultiBody(body->_native);
}

void MultiBodyDynamicsWorld::RemoveMultiBodyConstraint(MultiBodyConstraint^ constraint)
{
	Native->removeMultiBodyConstraint(constraint->_native);
}

#endif
