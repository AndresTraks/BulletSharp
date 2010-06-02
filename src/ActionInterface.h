#pragma once

// Fully implemented as of 29 May 2010

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class DebugDraw;

	public ref class ActionInterface : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btActionInterface* _actionInterface;

	internal:
		ActionInterface(btActionInterface* actionInterface);

	public:
		!ActionInterface();
	protected:
		~ActionInterface();

	public:
#ifndef DISABLE_DEBUGDRAW
		void DebugDraw(DebugDraw^ debugDrawer);
#endif
		void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btActionInterface* UnmanagedPointer
		{
			btActionInterface* get();
			void set(btActionInterface* value);
		}
	};
};
