#include "StdAfx.h"

#include "ActionInterface.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ActionInterface::ActionInterface(btActionInterface* actionInterface)
{
	_native = actionInterface;
}

ActionInterface::~ActionInterface()
{
	this->!ActionInterface();
}

ActionInterface::!ActionInterface()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	//delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

bool ActionInterface::IsDisposed::get()
{
	return ( _native == NULL );
}

#ifndef DISABLE_DEBUGDRAW
void ActionInterface::DebugDraw(IDebugDraw^ debugDrawer)
{
	_native->debugDraw(DebugDraw::GetUnmanaged(debugDrawer));
}
#endif

void ActionInterface::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_native->updateAction(collisionWorld->UnmanagedPointer, deltaTimeStep);
}
