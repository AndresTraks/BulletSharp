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
	DebugDrawWrapper* wrapper = dynamic_cast<DebugDrawWrapper*>(debugDrawer);
	if (wrapper) {
		_actionInterface->DebugDraw(static_cast<IDebugDraw^>(wrapper->_debugDraw.Target));
	} else if (_collisionWorld->_native->getDebugDrawer() == debugDrawer) {
		_actionInterface->DebugDraw(_collisionWorld->_debugDrawer);
	} else {
		throw gcnew NotImplementedException("Unknown debug drawer!");
	}
#endif
}

void ActionInterfaceWrapper::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	_actionInterface->UpdateAction(_collisionWorld, deltaTimeStep);
}
