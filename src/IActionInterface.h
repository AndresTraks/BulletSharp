#pragma once

namespace BulletSharp
{
	ref class CollisionWorld;
	interface class IDebugDraw;

	public interface class IActionInterface
	{
	public:
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);
	};

	// Wrapper for classes that are not RaycastVehicle or CharacterControllerInterface.
	class ActionInterfaceWrapper : public btActionInterface
	{
	public:
		gcroot<IActionInterface^> _actionInterface;
		gcroot<CollisionWorld^> _collisionWorld;

		ActionInterfaceWrapper(IActionInterface^ actionInterface, CollisionWorld^ collisionWorld);
		virtual ~ActionInterfaceWrapper();

		virtual void debugDraw(btIDebugDraw* debugDrawer);
		virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);
	};
};
