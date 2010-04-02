#pragma once

#include "Enums.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class StackAlloc;

	public ref class CollisionConfiguration abstract : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionConfiguration* _collisionConfiguration;

	protected:
		CollisionConfiguration( btCollisionConfiguration* collisionConfiguration );
	public:
		!CollisionConfiguration();
	protected:
		~CollisionConfiguration();
	public:
		CollisionAlgorithmCreateFunc^ GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property StackAlloc^ StackAllocator
		{
			StackAlloc^ get();
		}

	internal:
		property btCollisionConfiguration* UnmanagedPointer
		{
			virtual btCollisionConfiguration* get();
			void set( btCollisionConfiguration* value );
		}
	};
};
