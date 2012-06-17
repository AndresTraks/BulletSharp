#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"

CollisionObjectWrapper::CollisionObjectWrapper(btCollisionObjectWrapper* collisionObject)
{
	_unmanaged = collisionObject;
}

/*
CollisionObjectWrapper::CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape, CollisionObject^ collisionObject, Matrix worldTransform)
{
	btTransform* worldTransformTemp = Math::MatrixToBtTransform(worldTransform);
	_unmanaged = &btCollisionObjectWrapper(GetUnmanagedNullableNew(parent), GetUnmanagedNullable(shape),
		GetUnmanagedNullableNew(collisionObject), *worldTransformTemp);
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
		delete _unmanaged;
	}
	_unmanaged = NULL;
	
	OnDisposed(this, nullptr);
}
*/
void CollisionObjectWrapper::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_unmanaged->getWorldTransform(), outTransform);
}
/*
bool CollisionObjectWrapper::IsDisposed::get()
{
	return (_unmanaged == NULL);
}
*/

CollisionObject^ CollisionObjectWrapper::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_unmanaged->getCollisionObject());
}

CollisionShape^ CollisionObjectWrapper::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged((btCollisionShape*)_unmanaged->getCollisionShape());
}

Matrix CollisionObjectWrapper::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_unmanaged->getWorldTransform());
}
