#pragma once

#include "CollisionObject.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref struct BroadphasePair;
	ref class BroadphaseProxy;
	ref class CollisionAlgorithm;
	ref class CollisionDispatcher;
	ref class CollisionObjectWrapper;
	ref class DispatcherInfo;
	ref class OverlappingPairCache;
	ref class PersistentManifold;
	ref class PoolAllocator;
	interface class IDebugDraw;

	public ref class DispatcherInfo
	{
	public:
		enum class DispatchFunc
		{
			Discrete = btDispatcherInfo::DISPATCH_DISCRETE,
			Continuous = btDispatcherInfo::DISPATCH_CONTINUOUS
		};

	private:
		btDispatcherInfo* _info;

	internal:
		DispatcherInfo(btDispatcherInfo* info);

	public:
		property btScalar AllowedCcdPenetration
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ConvexConservativeDistanceThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

#ifndef DISABLE_DEBUGDRAW
		property IDebugDraw^ DebugDraw
		{
			IDebugDraw^ get();
			void set(IDebugDraw^ value);
		}
#endif

		property DispatchFunc DispatchFunction
		{
			DispatchFunc get();
			void set(DispatchFunc value);
		}

		property bool EnableSatConvex
		{
			bool get();
			void set(bool value);
		}

		property bool EnableSpu
		{
			bool get();
			void set(bool value);
		}

		property int StepCount
		{
			int get();
			void set(int value);
		}

		property btScalar TimeOfImpact
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar TimeStep
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool UseContinuous
		{
			bool get();
			void set(bool value);
		}

		property bool UseConvexConservativeDistanceUtil
		{
			bool get();
			void set(bool value);
		}

		property bool UseEpa
		{
			bool get();
			void set(bool value);
		}

	internal:
		property btDispatcherInfo* UnmanagedPointer
		{
			btDispatcherInfo* get();
			void set(btDispatcherInfo* value);
		}
	};

	public ref class Dispatcher : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btDispatcher* _native;
		Dispatcher(btDispatcher* dispatcher);

	public:
		!Dispatcher();
	protected:
		~Dispatcher();

	public:
		IntPtr AllocateCollisionAlgorithm(int size);
		void ClearManifold(PersistentManifold^ manifold);
		void DispatchAllCollisionPairs(OverlappingPairCache^ pairCache,
			DispatcherInfo^ dispatchInfo, Dispatcher^ dispatcher);
		CollisionAlgorithm^ FindAlgorithm(CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap, PersistentManifold^ sharedManifold);
		CollisionAlgorithm^ FindAlgorithm(CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap);
		void FreeCollisionAlgorithm(IntPtr ptr);
#ifndef DISABLE_INTERNAL
		//array<PersistentManifold^>^ GetInternalManifoldPointer();
		PersistentManifold^ GetManifoldByIndexInternal(int index);
#endif
		PersistentManifold^ GetNewManifold(CollisionObject^ body0, CollisionObject^ body1);
		bool NeedsCollision(CollisionObject^ body0, CollisionObject^ body1);
		bool NeedsResponse(CollisionObject^ body0, CollisionObject^ body1);
		void ReleaseManifold(PersistentManifold^ manifold);

		property int NumManifolds
		{
			int get();
		}

#ifndef DISABLE_UNCOMMON
		property PoolAllocator^ InternalManifoldPool
		{
			PoolAllocator^ get();
		}
#endif

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btDispatcher* UnmanagedPointer
		{
			btDispatcher* get();
			void set(btDispatcher* value);
		}
	};
};
