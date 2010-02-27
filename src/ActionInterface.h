#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionWorld;
	ref class DebugDraw;


	public ref class ActionInterface abstract
	{
	private:
		btActionInterface* _actionInterface;

	protected:
		ActionInterface(btActionInterface* actionInterface);

	public:
		void DebugDraw(DebugDraw^ debugDrawer);
		void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);

	internal:
		property btActionInterface* UnmanagedPointer
		{
			btActionInterface* get();
			void set(btActionInterface* value);
		}
	};
};
