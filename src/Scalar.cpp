#include "StdAfx.h"

#include "Scalar.h"

TypedObject::TypedObject(btTypedObject* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

TypedObject::~TypedObject()
{
	this->!TypedObject();
}

TypedObject::!TypedObject()
{
	if (!_preventDelete)
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
