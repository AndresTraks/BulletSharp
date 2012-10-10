#include "StdAfx.h"

#include "Scalar.h"

TypedObject::TypedObject(btTypedObject* typedObject)
{
	_native = typedObject;
}

ObjectType TypedObject::ObjectType::get()
{
	return (BulletSharp::ObjectType)_native->getObjectType();
}
void TypedObject::ObjectType::set(BulletSharp::ObjectType value)
{
	_native->m_objectType = (int)value;
}
