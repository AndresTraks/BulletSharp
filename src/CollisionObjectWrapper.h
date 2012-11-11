#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionShape;

	public ref class CollisionObjectWrapper // : BulletSharp::IDisposable
	{
	public:
		//virtual event EventHandler^ OnDisposing;
		//virtual event EventHandler^ OnDisposed;

	internal:
		btCollisionObjectWrapper* _native;

	private:
		//bool _doesNotOwnObject;

	internal:
		CollisionObjectWrapper(btCollisionObjectWrapper* collisionObjectWrapper);

/*
	public:
		!CollisionObjectWrapper();
	protected:
		~CollisionObjectWrapper();
*/

	public:
		//CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape, CollisionObject^ collisionObject, Matrix worldTransform, int partId, int index);

		void GetWorldTransform([Out] Matrix% outTransform);
/*
		property bool IsDisposed
		{
			virtual bool get();
		}
*/
		property CollisionObject^ CollisionObject
		{
			BulletSharp::CollisionObject^ get();
		}

		property CollisionShape^ CollisionShape
		{
			BulletSharp::CollisionShape^ get();
		}

		property int Index
		{
			int get();
			void set(int value);
		}

		property int PartID
		{
			int get();
			void set(int value);
		}

		property Matrix WorldTransform
		{
			Matrix get();
		}
	};
};
