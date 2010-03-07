#pragma once

// Fully implemented as of 07 Mar 2010

#include "CollisionObject.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class BroadphasePair;
	ref class BroadphaseProxy;
	ref class CollisionAlgorithm;
	ref class CollisionDispatcher;
	ref class DebugDraw;
	ref class DispatcherInfo;
	ref class OverlappingPairCache;
	ref class PersistentManifold;
	ref class StackAlloc;

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

		property BulletSharp::DebugDraw^ DebugDraw
		{
			BulletSharp::DebugDraw^ get();
			void set(BulletSharp::DebugDraw^ value);
		}

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

		property StackAlloc^ StackAllocator
		{
			StackAlloc^ get();
			void set(StackAlloc^ value);
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

	private:
		btDispatcher* _dispatcher;

	internal:
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
		CollisionAlgorithm^ FindAlgorithm(CollisionObject^ body0,
			CollisionObject^ body1, PersistentManifold^ sharedManifold);
		CollisionAlgorithm^ FindAlgorithm(CollisionObject^ body0,
			CollisionObject^ body1);
		void FreeCollisionAlgorithm(IntPtr ptr);
		//array<PersistentManifold^>^ GetInternalManifoldPointer();
		PersistentManifold^ GetManifoldByIndexInternal(int index);
		PersistentManifold^ GetNewManifold(IntPtr body0, IntPtr body1);
		bool NeedsCollision(CollisionObject^ body0, CollisionObject^ body1);
		bool NeedsResponse(CollisionObject^ body0, CollisionObject^ body1);
		void ReleaseManifold(PersistentManifold^ manifold);

		property int NumManifolds
		{
			int get();
		}

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
