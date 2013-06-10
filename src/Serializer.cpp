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

BulletSharp::Serializer::Serializer(btSerializer *serializer)
{
	_native = serializer;
}

void BulletSharp::Serializer::FinishSerialization()
{
	_native->finishSerialization();
}

void BulletSharp::Serializer::SerializeName(String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	_native->serializeName(nameTemp);
	StringConv::FreeUnmanagedString(nameTemp);
}

void BulletSharp::Serializer::StartSerialization()
{
	_native->startSerialization();
}

BulletSharp::DataStream^ BulletSharp::Serializer::LockBuffer()
{
	return gcnew DataStream((void*)_native->getBufferPointer(),
		_native->getCurrentBufferSize(), true, false, false);
}

int BulletSharp::Serializer::CurrentBufferSize::get()
{
	return _native->getCurrentBufferSize();
}

void BulletSharp::Serializer::RegisterNameForObject(Object^ obj, String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	CollisionShape^ shapeCast = dynamic_cast<CollisionShape^>(obj);
	if (shapeCast != nullptr)
	{
		_native->registerNameForPointer(shapeCast->_native, nameTemp);
		return;
	}

	CollisionObject^ objCast = dynamic_cast<CollisionObject^>(obj);
	if (objCast != nullptr)
	{
		_native->registerNameForPointer(objCast->_native, nameTemp);
		return;
	}

#ifndef DISABLE_CONSTRAINTS
	TypedConstraint^ constraintCast = dynamic_cast<TypedConstraint^>(obj);
	if (constraintCast != nullptr)
	{
		_native->registerNameForPointer(constraintCast->_native, nameTemp);
		return;
	}
#endif

	StringConv::FreeUnmanagedString(nameTemp);
}


#define Native static_cast<btDefaultSerializer*>(_native)

DefaultSerializer::DefaultSerializer()
: Serializer(new btDefaultSerializer())
{
}

void DefaultSerializer::WriteHeader([Out] String^% buffer)
{
	unsigned char* bufferTemp = new unsigned char[12];
	Native->writeHeader(bufferTemp);
	buffer = gcnew String(buffer);
	delete[] bufferTemp;
}

#endif
