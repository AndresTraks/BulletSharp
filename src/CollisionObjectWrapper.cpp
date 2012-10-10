#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"

CollisionObjectWrapper::CollisionObjectWrapper(btCollisionObjectWrapper* collisionObject)
{
	_native = collisionObject;
}

/*
CollisionObjectWrapper::CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape, CollisionObject^ collisionObject, Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_native = &btCollisionObjectWrapper(GetUnmanagedNullable(parent), GetUnmanagedNullable(shape),
		GetUnmanagedNullable(collisionObject), *worldTransformTemp);
	delete worldTransformTemp;
}

CollisionObjectWrapper::~CollisionObjectWrapper()
{
	this->!CollisionObjectWrapper();
}

CollisionObjectWrapper::!CollisionObjectWrapper()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);

	if (_doesNotOwnObject == false)
	{
		delete _native;
	}
	_native = NULL;
	
	OnDisposed(this, nullptr);
}
*/
void CollisionObjectWrapper::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_native->getWorldTransform(), outTransform);
}
/*
bool CollisionObjectWrapper::IsDisposed::get()
{
	return (_native == NULL);
}
*/

CollisionObject^ CollisionObjectWrapper::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->getCollisionObject());
}

CollisionShape^ CollisionObjectWrapper::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged((btCollisionShape*)_native->getCollisionShape());
}

Matrix CollisionObjectWrapper::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getWorldTransform());
}
