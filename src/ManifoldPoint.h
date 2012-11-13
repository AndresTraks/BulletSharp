#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	ref class ManifoldPoint;

	public delegate bool ContactAddedEventHandler(ManifoldPoint^ cp,
		CollisionObjectWrapper^ colObj0Wrap, int partId0, int index0,
		CollisionObjectWrapper^ colObj1Wrap, int partId1, int index1);

	public ref class ManifoldPoint
	{
	internal:
		btManifoldPoint* _native;
		static ContactAddedEventHandler^ _contactAdded;

		ManifoldPoint(btManifoldPoint* point);

	public:
		static event ContactAddedEventHandler^ ContactAdded
		{
			void add(ContactAddedEventHandler^ callback);
			void remove(ContactAddedEventHandler^ callback);
		}

	public:
		ManifoldPoint();
		ManifoldPoint(Vector3 pointA, Vector3 pointB, Vector3 normal, btScalar distance);

		property btScalar AppliedImpulse
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CombinedFriction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CombinedRestitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar CombinedRollingFriction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactCfm1
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactCfm2
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactMotion1
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactMotion2
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Distance
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Distance1
		{
			btScalar get();
			void set(btScalar value);
		}

		property int Index0
		{
			int get();
			void set(int value);
		}

		property int Index1
		{
			int get();
			void set(int value);
		}

		property Vector3 LateralFrictionDir1
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 LateralFrictionDir2
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property bool LateralFrictionInitialized
		{
			bool get();
			void set(bool value);
		}

		property int LifeTime
		{
			int get();
			void set(int value);
		}

		property Vector3 LocalPointA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 LocalPointB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 NormalWorldOnB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property int PartId0
		{
			int get();
			void set(int value);
		}

		property int PartId1
		{
			int get();
			void set(int value);
		}

		property Vector3 PositionWorldOnA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 PositionWorldOnB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Object^ UserPersistentData
		{
			Object^ get();
			void set(Object^ value);
		}
	};
};
