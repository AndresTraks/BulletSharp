#pragma once

namespace BulletSharp
{
	ref class CollisionWorld;
	interface class IDebugDraw;

	public interface class IAction
	{
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);
	};

	class ActionInterfaceWrapper : public btActionInterface
	{
	public:
		gcroot<IAction^> _actionInterface;
		gcroot<CollisionWorld^> _collisionWorld;

		ActionInterfaceWrapper(IAction^ actionInterface, CollisionWorld^ collisionWorld);
		virtual ~ActionInterfaceWrapper();

		virtual void debugDraw(btIDebugDraw* debugDrawer);
		virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);
	};
};
