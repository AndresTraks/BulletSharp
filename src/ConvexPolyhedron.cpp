#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "AlignedObjectArray.h"
#include "Collections.h"
#include "ConvexPolyhedron.h"

Face::Face()
{
	_face = new btFace();
}

/*
AlignedIntArray^ Face::ConnectedFaces::get()
{
	return gcnew AlignedIntArray(&_face->m_connectedFaces);
}
void Face::ConnectedFaces::set(AlignedIntArray^ value)
{
	_face->m_connectedFaces = *(btAlignedObjectArray<int>*)value->_unmanaged;
}
*/

AlignedIntArray^ Face::Indices::get()
{
	return gcnew AlignedIntArray(&_face->m_indices);
}

ScalarArray^ Face::Plane::get()
{
	return gcnew ScalarArray(_face->m_plane, 4);
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

void ConvexPolyhedron::Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj, [Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	VECTOR3_DEF(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = new btVector3;
	btVector3* witnesPtMaxTemp = new btVector3;
	
	_convexPolyhedron->project(*transformTemp, VECTOR3_USE(direction), minProjTemp, maxProjTemp, VECTOR3_USE(witnesPtMin), VECTOR3_USE(witnesPtMax));
	minProj = minProjTemp;
	maxProj = maxProjTemp;
	witnesPtMin = Math::BtVector3ToVector3(witnesPtMinTemp);
	witnesPtMax = Math::BtVector3ToVector3(witnesPtMaxTemp);

	delete witnesPtMaxTemp;
	delete witnesPtMinTemp;
	VECTOR3_DEL(direction);
	delete transformTemp;
}

bool ConvexPolyhedron::TestContainment()
{
	return _convexPolyhedron->testContainment();
}

Vector3 ConvexPolyhedron::C::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->mC);
}
void ConvexPolyhedron::C::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->mC);
}

Vector3 ConvexPolyhedron::E::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->mE);
}
void ConvexPolyhedron::E::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->mE);
}

Vector3 ConvexPolyhedron::Extents::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->m_extents);
}
void ConvexPolyhedron::Extents::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->m_extents);
}

Vector3 ConvexPolyhedron::LocalCenter::get()
{
	return Math::BtVector3ToVector3(&_convexPolyhedron->m_localCenter);
}
void ConvexPolyhedron::LocalCenter::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_convexPolyhedron->m_localCenter);
}

btScalar ConvexPolyhedron::Radius::get()
{
	return _convexPolyhedron->m_radius;
}
void ConvexPolyhedron::Radius::set(btScalar value)
{
	_convexPolyhedron->m_radius = value;
}

AlignedVector3Array^ ConvexPolyhedron::UniqueEdges::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_uniqueEdges);
}

AlignedVector3Array^ ConvexPolyhedron::Vertices::get()
{
	return gcnew AlignedVector3Array(&_convexPolyhedron->m_vertices);
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