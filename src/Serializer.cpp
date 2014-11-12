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

int BulletSharp::Serializer::NumChunks::get()
{
	return _native->getNumChunks();
}

int BulletSharp::Serializer::SerializationFlags::get()
{
	return _native->getSerializationFlags();
}
void BulletSharp::Serializer::SerializationFlags::set(int flags)
{
	_native->setSerializationFlags(flags);
}

/*
BulletSerializedArrays::BulletSerializedArrays(btBulletSerializedArrays* native)
{
	_native = native;
}

BulletSerializedArrays::~BulletSerializedArrays()
{
	this->!BulletSerializedArrays();
}

BulletSerializedArrays::!BulletSerializedArrays()
{
	delete _native;
	_native = NULL;
}

BulletSerializedArrays::BulletSerializedArrays()
{
	_native = new btBulletSerializedArrays();
}

AlignedQuantizedBvhDoubleDataArray^ BulletSerializedArrays::BvhsDouble::get()
{
	return _native->m_bvhsDouble;
}
void BulletSerializedArrays::BvhsDouble::set(AlignedQuantizedBvhDoubleDataArray^ value)
{
	_native->m_bvhsDouble = value->_native;
}

AlignedQuantizedBvhFloatDataArray^ BulletSerializedArrays::BvhsFloat::get()
{
	return _native->m_bvhsFloat;
}
void BulletSerializedArrays::BvhsFloat::set(AlignedQuantizedBvhFloatDataArray^ value)
{
	_native->m_bvhsFloat = value->_native;
}

AlignedCollisionObjectDoubleDataArray^ BulletSerializedArrays::CollisionObjectDataDouble::get()
{
	return _native->m_collisionObjectDataDouble;
}
void BulletSerializedArrays::CollisionObjectDataDouble::set(AlignedCollisionObjectDoubleDataArray^ value)
{
	_native->m_collisionObjectDataDouble = value->_native;
}

AlignedCollisionObjectFloatDataArray^ BulletSerializedArrays::CollisionObjectDataFloat::get()
{
	return _native->m_collisionObjectDataFloat;
}
void BulletSerializedArrays::CollisionObjectDataFloat::set(AlignedCollisionObjectFloatDataArray^ value)
{
	_native->m_collisionObjectDataFloat = value->_native;
}

AlignedCollisionShapeDataArray^ BulletSerializedArrays::ColShapeData::get()
{
	return _native->m_colShapeData;
}
void BulletSerializedArrays::ColShapeData::set(AlignedCollisionShapeDataArray^ value)
{
	_native->m_colShapeData = value->_native;
}

AlignedTypedConstraintDataArray^ BulletSerializedArrays::ConstraintData::get()
{
	return _native->m_constraintData;
}
void BulletSerializedArrays::ConstraintData::set(AlignedTypedConstraintDataArray^ value)
{
	_native->m_constraintData = value->_native;
}

AlignedTypedConstraintDoubleDataArray^ BulletSerializedArrays::ConstraintDataDouble::get()
{
	return _native->m_constraintDataDouble;
}
void BulletSerializedArrays::ConstraintDataDouble::set(AlignedTypedConstraintDoubleDataArray^ value)
{
	_native->m_constraintDataDouble = value->_native;
}

AlignedTypedConstraintFloatDataArray^ BulletSerializedArrays::ConstraintDataFloat::get()
{
	return _native->m_constraintDataFloat;
}
void BulletSerializedArrays::ConstraintDataFloat::set(AlignedTypedConstraintFloatDataArray^ value)
{
	_native->m_constraintDataFloat = value->_native;
}

AlignedDynamicsWorldDoubleDataArray^ BulletSerializedArrays::DynamicWorldInfoDataDouble::get()
{
	return _native->m_dynamicWorldInfoDataDouble;
}
void BulletSerializedArrays::DynamicWorldInfoDataDouble::set(AlignedDynamicsWorldDoubleDataArray^ value)
{
	_native->m_dynamicWorldInfoDataDouble = value->_native;
}

AlignedDynamicsWorldFloatDataArray^ BulletSerializedArrays::DynamicWorldInfoDataFloat::get()
{
	return _native->m_dynamicWorldInfoDataFloat;
}
void BulletSerializedArrays::DynamicWorldInfoDataFloat::set(AlignedDynamicsWorldFloatDataArray^ value)
{
	_native->m_dynamicWorldInfoDataFloat = value->_native;
}

AlignedRigidBodyDoubleDataArray^ BulletSerializedArrays::RigidBodyDataDouble::get()
{
	return _native->m_rigidBodyDataDouble;
}
void BulletSerializedArrays::RigidBodyDataDouble::set(AlignedRigidBodyDoubleDataArray^ value)
{
	_native->m_rigidBodyDataDouble = value->_native;
}

AlignedRigidBodyFloatDataArray^ BulletSerializedArrays::RigidBodyDataFloat::get()
{
	return _native->m_rigidBodyDataFloat;
}
void BulletSerializedArrays::RigidBodyDataFloat::set(AlignedRigidBodyFloatDataArray^ value)
{
	_native->m_rigidBodyDataFloat = value->_native;
}

AlignedbtSoftBodyDoubleDataArray^ BulletSerializedArrays::SoftBodyDoubleData::get()
{
	return _native->m_softBodyDoubleData;
}
void BulletSerializedArrays::SoftBodyDoubleData::set(AlignedbtSoftBodyDoubleDataArray^ value)
{
	_native->m_softBodyDoubleData = value->_native;
}

AlignedSoftBodyFloatDataArray^ BulletSerializedArrays::SoftBodyFloatData::get()
{
	return _native->m_softBodyFloatData;
}
void BulletSerializedArrays::SoftBodyFloatData::set(AlignedSoftBodyFloatDataArray^ value)
{
	_native->m_softBodyFloatData = value->_native;
}
*/

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
