#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
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
		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btCollisionConfiguration* UnmanagedPointer
		{
			virtual btCollisionConfiguration* get();
			void set( btCollisionConfiguration* value );
		}
	};
};
