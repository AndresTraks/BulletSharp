#pragma once

#include "IDisposable.h"
#include "Dispatcher.h"

namespace BulletSharp
{
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
		property bool IsDisposed
		{
			virtual bool get();
		}

	public:
		property btCollisionAlgorithm* UnmanagedPointer
		{
			virtual btCollisionAlgorithm* get();
			void set(btCollisionAlgorithm* value);
		}
	};
};
