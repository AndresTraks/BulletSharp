#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#include "CollisionObject.h"
#include "Serializer.h"
#include "StringConv.h"

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

IntPtr Serializer::BufferPointer::get()
{
	return IntPtr((void*)_serializer->getBufferPointer());
}

int Serializer::CurrentBufferSize::get()
{
	return _serializer->getCurrentBufferSize();
}

void Serializer::RegisterNameForObject(Object^ obj, String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	CollisionObject^ objCast = static_cast<CollisionObject^>(obj);
	if (objCast != nullptr)
		_serializer->registerNameForPointer(objCast->UnmanagedPointer, nameTemp);

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
