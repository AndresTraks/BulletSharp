#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#include "CollisionObject.h"
#include "CollisionShape.h"
#include "DataStream.h"
#include "Serializer.h"
#include "StringConv.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

Serializer::Serializer(btSerializer *serializer)
{
	_serializer = serializer;
}

void Serializer::FinishSerialization()
{
	_serializer->finishSerialization();
}

void Serializer::SerializeName(String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	_serializer->serializeName(nameTemp);
	StringConv::FreeUnmanagedString(nameTemp);
}

void Serializer::StartSerialization()
{
	_serializer->startSerialization();
}

BulletSharp::DataStream^ Serializer::LockBuffer()
{
	return gcnew DataStream((void*)_serializer->getBufferPointer(),
		_serializer->getCurrentBufferSize(), true, false, false);
}

int Serializer::CurrentBufferSize::get()
{
	return _serializer->getCurrentBufferSize();
}

void Serializer::RegisterNameForObject(Object^ obj, String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	CollisionShape^ shapeCast = dynamic_cast<CollisionShape^>(obj);
	if (shapeCast != nullptr)
	{
		_serializer->registerNameForPointer(shapeCast->UnmanagedPointer, nameTemp);
		return;
	}

	CollisionObject^ objCast = dynamic_cast<CollisionObject^>(obj);
	if (objCast != nullptr)
	{
		_serializer->registerNameForPointer(objCast->UnmanagedPointer, nameTemp);
		return;
	}

#ifndef DISABLE_CONSTRAINTS
	TypedConstraint^ constraintCast = dynamic_cast<TypedConstraint^>(obj);
	if (constraintCast != nullptr)
	{
		_serializer->registerNameForPointer(constraintCast->UnmanagedPointer, nameTemp);
		return;
	}
#endif

	StringConv::FreeUnmanagedString(nameTemp);
}

btSerializer* Serializer::UnmanagedPointer::get()
{
	return _serializer;
}
void Serializer::UnmanagedPointer::set(btSerializer* value)
{
	_serializer = value;
}


DefaultSerializer::DefaultSerializer(int totalSize)
: Serializer(new btDefaultSerializer(totalSize))
{
}

btDefaultSerializer* DefaultSerializer::UnmanagedPointer::get()
{
	return (btDefaultSerializer*)Serializer::UnmanagedPointer;
}

#endif
