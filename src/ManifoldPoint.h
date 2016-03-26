#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;
	ref class ManifoldPoint;

	[Flags]
	public enum class ContactPointFlags
	{
		None = 0,
		LateralFrictionInitialized = btContactPointFlags::BT_CONTACT_FLAG_LATERAL_FRICTION_INITIALIZED,
		HasContactCfm = btContactPointFlags::BT_CONTACT_FLAG_HAS_CONTACT_CFM,
		HasContactErp = btContactPointFlags::BT_CONTACT_FLAG_HAS_CONTACT_ERP
	};

#ifdef BT_CALLBACKS_ARE_EVENTS
	/*
	public ref class ContactAddedEventArgs : EventArgs
	{
	public:
		property ManifoldPoint^ ContactPoint;
		property CollisionObjectWrapper^ CollisionObject0Wrapper;
		property int PartID0;
		property int Index0;
		property CollisionObjectWrapper^ CollisionObject1Wrapper;
		property int PartID1;
		property int Index1;
		property bool IsContactModified;
	};
	public delegate void ContactAddedEventHandler(Object^ sender, ContactAddedEventArgs^ e);
	*/

	public delegate void ContactAddedEventHandler(ManifoldPoint^ cp,
		CollisionObjectWrapper^ colObj0Wrap, int partId0, int index0,
		CollisionObjectWrapper^ colObj1Wrap, int partId1, int index1);
#else
	public delegate bool ContactAdded(ManifoldPoint^ cp,
		CollisionObjectWrapper^ colObj0Wrap, int partId0, int index0,
		CollisionObjectWrapper^ colObj1Wrap, int partId1, int index1);
#endif

	public ref class ManifoldPoint
	{
	internal:
		btManifoldPoint* _native;

	private:
		bool _preventDelete;

	internal:
		ManifoldPoint(btManifoldPoint* native, bool preventDelete);
#ifdef BT_CALLBACKS_ARE_EVENTS
		static ContactAddedEventHandler^ _contactAdded;
	public:
		static event ContactAddedEventHandler^ ContactAdded
		{
			void add(ContactAddedEventHandler^ callback);
			void remove(ContactAddedEventHandler^ callback);
		}
#else
		static ContactAdded^ _contactAdded;
	public:
		static property ContactAdded^ ContactAdded
		{
			::ContactAdded^ get();
			void set(::ContactAdded^ value);
		}
#endif

		~ManifoldPoint();
		!ManifoldPoint();

	public:
		ManifoldPoint();
		ManifoldPoint(Vector3 pointA, Vector3 pointB, Vector3 normal, btScalar distance);

		property btScalar AppliedImpulse
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AppliedImpulseLateral1
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AppliedImpulseLateral2
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

		property btScalar ContactCfm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactErp
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

		property BulletSharp::ContactPointFlags ContactPointFlags
		{
			BulletSharp::ContactPointFlags get();
			void set(BulletSharp::ContactPointFlags value);
		}

		property btScalar Distance
		{
			btScalar get();
			void set(btScalar dist);
		}

		property btScalar Distance1
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar FrictionCfm
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
