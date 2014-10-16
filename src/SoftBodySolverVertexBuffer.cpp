#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "Collections.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::VertexBufferDescriptor::VertexBufferDescriptor(btVertexBufferDescriptor* native)
{
	_native = native;
}

SoftBody::VertexBufferDescriptor::~VertexBufferDescriptor()
{
	this->!VertexBufferDescriptor();
}

SoftBody::VertexBufferDescriptor::!VertexBufferDescriptor()
{
	delete _native;
	_native = NULL;
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

SoftBody::CpuVertexBufferDescriptor::CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset,
	int vertexStride)
	: VertexBufferDescriptor(new btCPUVertexBufferDescriptor((float*)array->_native,
		vertexOffset, vertexStride))
{
	_vertexBuffer = array;
}

SoftBody::CpuVertexBufferDescriptor::CpuVertexBufferDescriptor(FloatArray^ array, int vertexOffset,
	int vertexStride, int normalOffset, int normalStride)
	: VertexBufferDescriptor(new btCPUVertexBufferDescriptor((float*)array->_native,
		vertexOffset, vertexStride, normalOffset, normalStride))
{
	_vertexBuffer = array;
}

IntPtr SoftBody::CpuVertexBufferDescriptor::BasePointer::get()
{
	return IntPtr(Native->getBasePointer());
}

FloatArray^ SoftBody::CpuVertexBufferDescriptor::VertexBuffer::get()
{
	return _vertexBuffer;
}

#endif
