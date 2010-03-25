#include "StdAfx.h"

#include "ActionInterface.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ActionInterface::ActionInterface(btActionInterface* actionInterface)
{
	_actionInterface = actionInterface;
}

#ifndef DISABLE_DEBUGDRAW
void ActionInterface::DebugDraw(BulletSharp::DebugDraw^ debugDrawer)
{
	_actionInterface->debugDraw(debugDrawer->UnmanagedPointer);
}
#endif

void ActionInterface::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_actionInterface->updateAction(collisionWorld->UnmanagedPointer, deltaTimeStep);
}

btActionInterface* ActionInterface::UnmanagedPointer::get()
{
	return _actionInterface;
}
void ActionInterface::UnmanagedPointer::set(btActionInterface* value)
{
	_actionInterface = value;
}
