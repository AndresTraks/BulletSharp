#pragma once

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
	//ref class StackAlloc;

	public ref class DispatcherInfo
	{
	public:
		enum class DispatchFunc
		{
			Discrete = 1,
			Continuous
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

		//property StackAlloc^ StackAllocator
		//{
		//	int get();
		//	void set(int value);
		//}

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
		CollisionAlgorithm^ FindAlgorithm(CollisionObject^ body0,
			CollisionObject^ body1);
		//CollisionAlgorithm^ FindAlgorithm(CollisionObject^ body0,
		//	CollisionObject^ body1, PersistentManifold^ sharedManifold);

		bool NeedsCollision(CollisionObject^ body0, CollisionObject^ body1);

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
