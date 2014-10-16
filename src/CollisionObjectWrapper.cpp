#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"

CollisionObjectWrapper::CollisionObjectWrapper(btCollisionObjectWrapper* native)
{
	_native = native;
}
/*
CollisionObjectWrapper::CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape,
	CollisionObject^ collisionObject, Matrix worldTransform, int partId, int index)
{
	TRANSFORM_CONV(worldTransform);
	_native = &btCollisionObjectWrapper(GetUnmanagedNullable(parent), GetUnmanagedNullable(shape),
		GetUnmanagedNullable(collisionObject), TRANSFORM_USE(worldTransform), partId, index);
	TRANSFORM_DEL(worldTransform);
}

CollisionObjectWrapper::~CollisionObjectWrapper()
{
	this->!CollisionObjectWrapper();
}

CollisionObjectWrapper::!CollisionObjectWrapper()
{
	if (this->IsDisposed)
		return;

	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
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

int CollisionObjectWrapper::Index::get()
{
	return _native->m_index;
}
void CollisionObjectWrapper::Index::set(int value)
{
	_native->m_index = value;
}

int CollisionObjectWrapper::PartID::get()
{
	return _native->m_partId;
}
void CollisionObjectWrapper::PartID::set(int value)
{
	_native->m_partId = value;
}

Matrix CollisionObjectWrapper::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getWorldTransform());
}
