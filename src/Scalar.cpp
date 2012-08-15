#include "StdAfx.h"

#include "Scalar.h"

TypedObject::TypedObject(btTypedObject* typedObject)
{
	_unmanaged = typedObject;
}

ObjectType TypedObject::ObjectType::get()
{
	return (BulletSharp::ObjectType)_unmanaged->getObjectType();
}
void TypedObject::ObjectType::set(BulletSharp::ObjectType value)
{
	_unmanaged->m_objectType = (int)value;
}
