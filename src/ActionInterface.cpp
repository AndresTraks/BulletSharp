#include "StdAfx.h"

#include "ActionInterface.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ActionInterface::ActionInterface(btActionInterface* actionInterface)
{
	_unmanaged = actionInterface;
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

	//delete _unmanaged;
	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

bool ActionInterface::IsDisposed::get()
{
	return ( _unmanaged == NULL );
}

#ifndef DISABLE_DEBUGDRAW
void ActionInterface::DebugDraw(IDebugDraw^ debugDrawer)
{
	_unmanaged->debugDraw(DebugDraw::GetUnmanaged(debugDrawer));
}
#endif

void ActionInterface::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_unmanaged->updateAction(collisionWorld->UnmanagedPointer, deltaTimeStep);
}
