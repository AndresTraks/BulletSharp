#include "StdAfx.h"

#include "Scalar.h"

TypedObject::TypedObject(btTypedObject* native)
{
	_native = native;
}

TypedObject::~TypedObject()
{
	this->!TypedObject();
}

TypedObject::!TypedObject()
{
	delete _native;
	_native = NULL;
}

ObjectType TypedObject::ObjectType::get()
{
	return (BulletSharp::ObjectType)_native->getObjectType();
}
void TypedObject::ObjectType::set(BulletSharp::ObjectType value)
{
	_native->m_objectType = (int)value;
}
