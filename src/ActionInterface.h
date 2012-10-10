#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	interface class IDebugDraw;

	public ref class ActionInterface : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btActionInterface* _native;
		ActionInterface(btActionInterface* actionInterface);

	public:
		!ActionInterface();
	protected:
		~ActionInterface();

	public:
#ifndef DISABLE_DEBUGDRAW
		void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
