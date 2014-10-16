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

BulletSharp::Serializer::Serializer(btSerializer* native)
{
	_native = native;
}

BulletSharp::Serializer::~Serializer()
{
	this->!Serializer();
}

BulletSharp::Serializer::!Serializer()
{
	delete _native;
	_native = NULL;
}
/*
Chunk^ BulletSharp::Serializer::Allocate(int size, int numElements)
{
	return _native->allocate(size, numElements);
}

void BulletSharp::Serializer::FinalizeChunk(Chunk^ chunk, char^ structType, int chunkCode, IntPtr oldPtr)
{
	_native->finalizeChunk(chunk->_native, structType->_native, chunkCode, oldPtr.ToPointer());
}

String^ BulletSharp::Serializer::FindNameForPointer(IntPtr ptr)
{
	return _native->findNameForPointer(ptr.ToPointer());
}

IntPtr BulletSharp::Serializer::FindPointer(IntPtr oldPtr)
{
	return _native->findPointer(oldPtr.ToPointer());
}
*/
void BulletSharp::Serializer::FinishSerialization()
{
	_native->finishSerialization();
}
/*
IntPtr BulletSharp::Serializer::GetUniquePointer(IntPtr oldPtr)
{
	return _native->getUniquePointer(oldPtr.ToPointer());
}
*/
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

IntPtr BulletSharp::Serializer::BufferPointer::get()
{
	return IntPtr((void*)_native->getBufferPointer());
}

int BulletSharp::Serializer::CurrentBufferSize::get()
{
	return _native->getCurrentBufferSize();
}

int BulletSharp::Serializer::SerializationFlags::get()
{
	return _native->getSerializationFlags();
}
void BulletSharp::Serializer::SerializationFlags::set(int flags)
{
	_native->setSerializationFlags(flags);
}



#define Native static_cast<btDefaultSerializer*>(_native)

DefaultSerializer::DefaultSerializer(int totalSize)
	: Serializer(new btDefaultSerializer(totalSize))
{
}

DefaultSerializer::DefaultSerializer()
	: Serializer(new btDefaultSerializer())
{
}
/*
IntPtr DefaultSerializer::InternalAlloc(int size)
{
	return Native->internalAlloc(size);
}
*/
void DefaultSerializer::WriteHeader([Out] String^% buffer)
{
	unsigned char* bufferTemp = new unsigned char[12];
	Native->writeHeader(bufferTemp);
	buffer = gcnew String(buffer);
	delete[] bufferTemp;
}

#endif
