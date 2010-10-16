#pragma once

// Fully implemented as of 27 Feb 2010

#include "IDisposable.h"

namespace BulletSharp
{
	ref class Dispatcher;
	ref class DispatcherInfo;
	ref class CollisionObject;
	ref class ManifoldResult;
	ref class AlignedManifoldArray;
	ref class PersistentManifold;

	public ref class CollisionAlgorithmConstructionInfo
	{
	private:
		btCollisionAlgorithmConstructionInfo* _info;

	public:
		CollisionAlgorithmConstructionInfo();
		CollisionAlgorithmConstructionInfo(Dispatcher^ dispatcher, int temp);

		property BulletSharp::Dispatcher^ Dispatcher
		{
			BulletSharp::Dispatcher^ get();
			void set(BulletSharp::Dispatcher^ value);
		}

		property PersistentManifold^ Manifold
		{
			PersistentManifold^ get();
			void set(PersistentManifold^ value);
		}

	internal:
		property btCollisionAlgorithmConstructionInfo* UnmanagedPointer
		{
			virtual btCollisionAlgorithmConstructionInfo* get();
			void set(btCollisionAlgorithmConstructionInfo* value);
		}
	};

	public ref class CollisionAlgorithm : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionAlgorithm* _algorithm;

	internal:
		CollisionAlgorithm(btCollisionAlgorithm* algorithm);

	public:
		!CollisionAlgorithm();
	protected:
		~CollisionAlgorithm();

	public:
		btScalar CalculateTimeOfImpact(CollisionObject^ body0, CollisionObject^ body1,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);
		void GetAllContactManifolds(AlignedManifoldArray^ manifoldArray);
		void ProcessCollision(CollisionObject^ body0, CollisionObject^ body1,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btCollisionAlgorithm* UnmanagedPointer
		{
			virtual btCollisionAlgorithm* get();
			void set(btCollisionAlgorithm* value);
		}
	};
};
