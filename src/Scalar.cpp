#include "StdAfx.h"

#include "Scalar.h"

TypedObject::TypedObject(btTypedObject* typedObject)
{
	_typedObject = typedObject;
}

ObjectType TypedObject::ObjectType::get()
{
	return (BulletSharp::ObjectType)_typedObject->getObjectType();
}
void TypedObject::ObjectType::set(BulletSharp::ObjectType value)
{
	_typedObject->m_objectType = (int)value;
}

btTypedObject* TypedObject::UnmanagedPointer::get()
{
	return _typedObject;
}
void TypedObject::UnmanagedPointer::set(btTypedObject* value)
{
	_typedObject = value;
}
