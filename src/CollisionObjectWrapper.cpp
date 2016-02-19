#include "StdAfx.h"

#include "Collections.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"
#include "CompoundShape.h"

CollisionObjectWrapper::CollisionObjectWrapper(btCollisionObjectWrapper* native)
{
	_native = native;
}
/*
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

CollisionObjectWrapper::CollisionObjectWrapper(CollisionObjectWrapper^ parent, CollisionShape^ shape,
	CollisionObject^ collisionObject, Matrix worldTransform, int partId, int index)
{
	TRANSFORM_CONV(worldTransform);
	_native = new btCollisionObjectWrapper(GetUnmanagedNullable(parent), GetUnmanagedNullable(shape), GetUnmanagedNullable(collisionObject),
		TRANSFORM_USE(worldTransform), partId, index);
	TRANSFORM_DEL(worldTransform);
}
*/
void CollisionObjectWrapper::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_native->getWorldTransform(), outTransform);
}

CollisionObject^ CollisionObjectWrapper::CollisionObject::get()
{
	return BulletSharp::CollisionObject::GetManaged((btCollisionObject*)_native->getCollisionObject());
}

CollisionShape^ CollisionObjectWrapper::CollisionShape::get()
{
	btCollisionShape* collisionShapePtr = (btCollisionShape*)_native->getCollisionShape();
	BulletSharp::CollisionShape^ collisionShape = CollisionObject->CollisionShape;
	if (collisionShape->_native == collisionShapePtr)
		return collisionShape;

	// Recursively look for compound shape child shape
	if (collisionShape->_native->getShapeType() == COMPOUND_SHAPE_PROXYTYPE)
	{
		BulletSharp::CollisionShape^ childShape = static_cast<CompoundShape^>(collisionShape)->GetChildShapeByPtr(collisionShapePtr, _native->m_index);
		if (childShape) return childShape;
	}

	//throw gcnew NotImplementedException();
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

/*
bool CollisionObjectWrapper::IsDisposed::get()
{
	return (_native == NULL);
}
*/

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
