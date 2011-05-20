#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionAlgorithm;
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObject;

	public ref class CollisionAlgorithmCreateFunc : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionAlgorithmCreateFunc* _createFunc;

	internal:
		CollisionAlgorithmCreateFunc(btCollisionAlgorithmCreateFunc* solver);

	public:
		!CollisionAlgorithmCreateFunc();
	protected:
		~CollisionAlgorithmCreateFunc();

	public:
		CollisionAlgorithmCreateFunc();

		CollisionAlgorithm^ CreateCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ info,
			CollisionObject^ body0, CollisionObject^ body1);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool Swapped
		{
			bool get();
			void set(bool value);
		}

	internal:
		property btCollisionAlgorithmCreateFunc* UnmanagedPointer
		{
			virtual btCollisionAlgorithmCreateFunc* get();
			void set(btCollisionAlgorithmCreateFunc* value);
		}
	};
};
