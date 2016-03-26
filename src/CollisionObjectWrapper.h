#pragma once

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionShape;

	public ref class CollisionObjectWrapper //
	{
	internal:
		btCollisionObjectWrapper* _native;

	private:
		//bool _preventDelete;

	internal:
		CollisionObjectWrapper(btCollisionObjectWrapper* native);
/*
		~CollisionObjectWrapper();
		!CollisionObjectWrapper();
*/

	public:
		//CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape,
		//	CollisionObject^ collisionObject, Matrix worldTransform, int partId, int index);

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
