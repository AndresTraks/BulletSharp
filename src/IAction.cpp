#include "StdAfx.h"

#include "IAction.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ActionInterfaceWrapper::ActionInterfaceWrapper(IAction^ actionInterface, CollisionWorld^ collisionWorld)
{
	_actionInterface = actionInterface;
	_collisionWorld = collisionWorld;
}

ActionInterfaceWrapper::~ActionInterfaceWrapper()
{
}

void ActionInterfaceWrapper::debugDraw(btIDebugDraw* debugDrawer)
{
#ifndef DISABLE_DEBUGDRAW
	_actionInterface->DebugDraw(DebugDraw::GetManaged(debugDrawer));
#endif
}

void ActionInterfaceWrapper::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	_actionInterface->UpdateAction(_collisionWorld, deltaTimeStep);
}