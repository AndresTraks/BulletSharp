#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face()
{
	_face = new btFace();
}

AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_face->m_connectedFaces);
}
void Face::ConnectedFaces::set(AlignedIntArray^ value)
{
	_face->m_connectedFaces = *value->UnmanagedPointer;
}

AlignedIntArray^ Face::Indices::get()
{
	return gcnew AlignedIntArray(&_face->m_indices);
}
void Face::Indices::set(AlignedIntArray^ value)
{
	_face->m_indices = *value->UnmanagedPointer;
}

FloatArray^ Face::Plane::get()
{
	return gcnew FloatArray(_face->m_plane, 4);
}

btFace* Face::UnmanagedPointer::get()
{
	return _face;
}
void Face::UnmanagedPointer::set(btFace* value)
{
	_face = value;
}


ConvexPolyhedron::ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron)
{
	_convexPolyhedron = convexPolyhedron;
}

ConvexPolyhedron::ConvexPolyhedron()
{
	_convexPolyhedron = new btConvexPolyhedron();
}

ConvexPolyhedron::~ConvexPolyhedron()
{
	this->!ConvexPolyhedron();
}

ConvexPolyhedron::!ConvexPolyhedron()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_convexPolyhedron = NULL;

	OnDisposed(this, nullptr);
}

bool ConvexPolyhedron::IsDisposed::get()
{
	return _convexPolyhedron == NULL;
}

void ConvexPolyhedron::Initialize()
{
	_convexPolyhedron->initialize();
}

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] float% min, [Out] float% max)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	btVector3* directionTemp = Math::Vector3ToBtVector3(direction);
	float minTemp;
	float maxTemp;
	
	_convexPolyhedron->project(*transformTemp, *directionTemp, minTemp, maxTemp);
	min = minTemp;
	max = maxTemp;
	
	delete directionTemp;
	delete transformTemp;
}

Vector3 ConvexPolyhedron::LocalCenter::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->m_localCenter);
}
void ConvexPolyhedron::LocalCenter::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->m_localCenter);
}

AlignedVector3Array^ ConvexPolyhedron::UniqueEdges::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_uniqueEdges);
}
void ConvexPolyhedron::UniqueEdges::set(AlignedVector3Array^ value)
{
	_convexPolyhedron->m_uniqueEdges = *value->UnmanagedPointer;
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_vertices);
}
void ConvexPolyhedron::Vertices::set(AlignedVector3Array^ value)
{
	_convexPolyhedron->m_vertices = *value->UnmanagedPointer;
}

btConvexPolyhedron* ConvexPolyhedron::UnmanagedPointer::get()
{
	return _convexPolyhedron;
}
void ConvexPolyhedron::UnmanagedPointer::set(btConvexPolyhedron* value)
{
	_convexPolyhedron = value;
}

#endif