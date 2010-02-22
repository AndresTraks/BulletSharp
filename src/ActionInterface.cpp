#include "StdAfx.h"

#include "ActionInterface.h"

ActionInterface::ActionInterface(btActionInterface* actionInterface)
{
	_actionInterface = actionInterface;
}

void ActionInterface::DebugDraw(BulletSharp::DebugDraw^ debugDrawer)
{
	_actionInterface->debugDraw(debugDrawer->_debugWrapper);
}

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
