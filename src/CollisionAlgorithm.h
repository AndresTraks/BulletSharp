#pragma once

namespace BulletSharp
{
	ref class AlignedManifoldArray;
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class Dispatcher;
	ref class DispatcherInfo;
	ref class ManifoldResult;
	ref class PersistentManifold;

	public ref class CollisionAlgorithmConstructionInfo : IDisposable
	{
	internal:
		btCollisionAlgorithmConstructionInfo* _native;

	private:
		Dispatcher^ _dispatcher;
		PersistentManifold^ _manifold;

	public:
		!CollisionAlgorithmConstructionInfo();
	protected:
		~CollisionAlgorithmConstructionInfo();

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
	};

	public ref class CollisionAlgorithm : IDisposable // abstract
	{
	internal:
		btCollisionAlgorithm* _native;

	private:
		bool _preventDelete;

	internal:
		CollisionAlgorithm(btCollisionAlgorithm* native);
		CollisionAlgorithm(btCollisionAlgorithm* native, bool preventDelete);
		static CollisionAlgorithm^ GetManaged(btCollisionAlgorithm* native);

	public:
		!CollisionAlgorithm();
	protected:
		~CollisionAlgorithm();

	public:
		btScalar CalculateTimeOfImpact(CollisionObject^ body0, CollisionObject^ body1,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);
		void GetAllContactManifolds(AlignedManifoldArray^ manifoldArray);
		void ProcessCollision(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			DispatcherInfo^ dispatchInfo, ManifoldResult^ resultOut);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
