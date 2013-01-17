#pragma once

#include "Scalar.h"

namespace BulletSharp
{
	ref class ManifoldPoint;
	
#ifdef BT_CALLBACKS_ARE_EVENTS
	public delegate void ContactDestroyedEventHandler(Object^ userPersistantData);
	public delegate void ContactProcessedEventHandler(ManifoldPoint^ cp, CollisionObject^ body0, CollisionObject^ body1);
#else
	public delegate bool ContactDestroyed(Object^ userPersistantData);
	public delegate bool ContactProcessed(ManifoldPoint^ cp, CollisionObject^ body0, CollisionObject^ body1);
#endif

	public ref class PersistentManifold : TypedObject
	{
	internal:
		PersistentManifold(btPersistentManifold* manifold);

#ifdef BT_CALLBACKS_ARE_EVENTS
		static ContactDestroyedEventHandler^ _contactDestroyed;
		static ContactProcessedEventHandler^ _contactProcessed;

	public:
		static event ContactDestroyedEventHandler^ ContactDestroyed
		{
			void add(ContactDestroyedEventHandler^ callback);
			void remove(ContactDestroyedEventHandler^ callback);
		}
		static event ContactProcessedEventHandler^ ContactProcessed
		{
			void add(ContactProcessedEventHandler^ callback);
			void remove(ContactProcessedEventHandler^ callback);
		}
#else
		static ContactDestroyed^ _contactDestroyed;
		static ContactProcessed^ _contactProcessed;

		static property ContactDestroyed^ ContactDestroyed
		{
			::ContactDestroyed^ get();
			void set(::ContactDestroyed^ value);
		}

		static property ContactProcessed^ ContactProcessed
		{
			::ContactProcessed^ get();
			void set(::ContactProcessed^ value);
		}
#endif

		PersistentManifold();
		//PersistentManifold(Object^ body0, Object^ body1, int , btScalar contactBreakingThreshold, btScalar contactProcessingThreshold);

		int AddManifoldPoint(ManifoldPoint^ newPoint, bool isPredictive);
		int AddManifoldPoint(ManifoldPoint^ newPoint);
		void ClearManifold();
		void ClearUserCache(ManifoldPoint^ pt);
#ifdef DEBUG_PERSISTENCY
		void DebugPersistency();
#endif
		int GetCacheEntry(ManifoldPoint^ newPoint);
		ManifoldPoint^ GetContactPoint(int index);
		void RefreshContactPoints(Matrix trA, Matrix trB);
		void RemoveContactPoint(int index);
		void ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex);
		//void SetBodies(Object^ body0, Object^ body1);
		bool ValidContactDistance(ManifoldPoint^ pt);

		property Object^ Body0
		{
			Object^ get();
		}

		property Object^ Body1
		{
			Object^ get();
		}

		property int CompanionIDA
		{
			int get();
			void set(int value);
		}

		property int CompanionIDB
		{
			int get();
			void set(int value);
		}

		property btScalar ContactBreakingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ContactProcessingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property int Index1A
		{
			int get();
			void set(int value);
		}

		property int NumContacts
		{
			int get();
			void set(int value);
		}
	};
};
