#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "Collections.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::VertexBufferDescriptor::VertexBufferDescriptor(btVertexBufferDescriptor* buffer)
{
	_buffer = buffer;
}

BufferType SoftBody::VertexBufferDescriptor::BufferType::get()
{
	return (BulletSharp::BufferType)_buffer->getBufferType();
}

bool SoftBody::VertexBufferDescriptor::HasNormals::get()
{
	return _buffer->hasNormals();
}

bool SoftBody::VertexBufferDescriptor::HasVertexPositions::get()
{
	return _buffer->hasVertexPositions();
}

int SoftBody::VertexBufferDescriptor::NormalOffset::get()
{
	return _buffer->getNormalOffset();
}

int SoftBody::VertexBufferDescriptor::NormalStride::get()
{
	return _buffer->getNormalStride();
}

int SoftBody::VertexBufferDescriptor::VertexOffset::get()
{
	return _buffer->getVertexOffset();
}

int SoftBody::VertexBufferDescriptor::VertexStride::get()
{
	return _buffer->getVertexStride();
}

btVertexBufferDescriptor* SoftBody::VertexBufferDescriptor::UnmanagedPointer::get()
{
	return _buffer;
}
void SoftBody::VertexBufferDescriptor::UnmanagedPointer::set(btVertexBufferDescriptor* value)
{
	_buffer = value;
}


SoftBody::CpuVertexBufferDescriptor::CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride, int normalOffset, int normalStride)
: VertexBufferDescriptor(new btCPUVertexBufferDescriptor((array != nullptr) ? (btScalar*)array->_unmanaged : 0, vertexOffset, vertexStride, normalOffset, normalStride))
{
	_length = array->Count;
}

FloatArray^ SoftBody::CpuVertexBufferDescriptor::VertexBuffer::get()
{
	return gcnew FloatArray(UnmanagedPointer->getBasePointer(), _length);
}

btCPUVertexBufferDescriptor* SoftBody::CpuVertexBufferDescriptor::UnmanagedPointer::get()
{
	return (btCPUVertexBufferDescriptor*) VertexBufferDescriptor::UnmanagedPointer;
}

#endif
