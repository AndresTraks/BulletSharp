#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "Collections.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::VertexBufferDescriptor::VertexBufferDescriptor(btVertexBufferDescriptor* native)
{
	_native = native;
}

BufferType SoftBody::VertexBufferDescriptor::BufferType::get()
{
	return (BulletSharp::BufferType)_native->getBufferType();
}

bool SoftBody::VertexBufferDescriptor::HasNormals::get()
{
	return _native->hasNormals();
}

bool SoftBody::VertexBufferDescriptor::HasVertexPositions::get()
{
	return _native->hasVertexPositions();
}

int SoftBody::VertexBufferDescriptor::NormalOffset::get()
{
	return _native->getNormalOffset();
}

int SoftBody::VertexBufferDescriptor::NormalStride::get()
{
	return _native->getNormalStride();
}

int SoftBody::VertexBufferDescriptor::VertexOffset::get()
{
	return _native->getVertexOffset();
}

int SoftBody::VertexBufferDescriptor::VertexStride::get()
{
	return _native->getVertexStride();
}


#define Native static_cast<btCPUVertexBufferDescriptor*>(_native)

SoftBody::CpuVertexBufferDescriptor::CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset, int vertexStride, int normalOffset, int normalStride)
: VertexBufferDescriptor(new btCPUVertexBufferDescriptor((array != nullptr) ? (float*)array->_native : 0, vertexOffset, vertexStride, normalOffset, normalStride))
{
	_length = (array != nullptr) ? array->Count : 0;
}

FloatArray^ SoftBody::CpuVertexBufferDescriptor::VertexBuffer::get()
{
	return gcnew FloatArray(Native->getBasePointer(), _length);
}

#endif
