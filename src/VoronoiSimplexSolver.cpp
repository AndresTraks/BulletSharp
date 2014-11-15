#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Collections.h"
#include "VoronoiSimplexSolver.h"

SubSimplexClosestResult::SubSimplexClosestResult(btSubSimplexClosestResult* native)
{
	_native = native;
}

SubSimplexClosestResult::~SubSimplexClosestResult()
{
	this->!SubSimplexClosestResult();
}

SubSimplexClosestResult::!SubSimplexClosestResult()
{
	delete _native;
	_native = NULL;
}

SubSimplexClosestResult::SubSimplexClosestResult()
{
	_native = new btSubSimplexClosestResult();
}

void SubSimplexClosestResult::Reset()
{
	_native->reset();
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c,
	btScalar d)
{
	_native->setBarycentricCoordinates(a, b, c, d);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c)
{
	_native->setBarycentricCoordinates(a, b, c);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b)
{
	_native->setBarycentricCoordinates(a, b);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a)
{
	_native->setBarycentricCoordinates(a);
}

void SubSimplexClosestResult::SetBarycentricCoordinates()
{
	_native->setBarycentricCoordinates();
}

ScalarArray^ SubSimplexClosestResult::BarycentricCoords::get()
{
	if (_barycentricCoords == nullptr)
	{
		_barycentricCoords = gcnew ScalarArray(_native->m_barycentricCoords, 4);
	}
	return _barycentricCoords;
}

Vector3 SubSimplexClosestResult::ClosestPointOnSimplex::get()
{
	return Math::BtVector3ToVector3(&_native->m_closestPointOnSimplex);
}
void SubSimplexClosestResult::ClosestPointOnSimplex::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_closestPointOnSimplex);
}

bool SubSimplexClosestResult::Degenerate::get()
{
	return _native->m_degenerate;
}
void SubSimplexClosestResult::Degenerate::set(bool value)
{
	_native->m_degenerate = value;
}

bool SubSimplexClosestResult::IsValid::get()
{
	return _native->isValid();
}
/*
UsageBitfield^ SubSimplexClosestResult::UsedVertices::get()
{
	return _native->m_usedVertices;
}
void SubSimplexClosestResult::UsedVertices::set(UsageBitfield^ value)
{
	_native->m_usedVertices = value->_native;
}
*/


#ifdef NO_VIRTUAL_INTERFACE
VoronoiSimplexSolver::VoronoiSimplexSolver(btVoronoiSimplexSolver* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

VoronoiSimplexSolver::~VoronoiSimplexSolver()
{
	this->!SimplexSolverInterface();
}

VoronoiSimplexSolver::!VoronoiSimplexSolver()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

#else
VoronoiSimplexSolver::VoronoiSimplexSolver(btVoronoiSimplexSolver* native)
{
	_native = native;
}
#endif

VoronoiSimplexSolver::VoronoiSimplexSolver()
{
	_native = new btVoronoiSimplexSolver();
}

void VoronoiSimplexSolver::AddVertex(Vector3 w, Vector3 p, Vector3 q)
{
	VECTOR3_CONV(w);
	VECTOR3_CONV(p);
	VECTOR3_CONV(q);
	_native->addVertex(VECTOR3_USE(w), VECTOR3_USE(p), VECTOR3_USE(q));
	VECTOR3_DEL(w);
	VECTOR3_DEL(p);
	VECTOR3_DEL(q);
}

void VoronoiSimplexSolver::BackupClosest(Vector3 v)
{
	VECTOR3_CONV(v);
	_native->backup_closest(VECTOR3_USE(v));
	VECTOR3_DEL(v);
}

bool VoronoiSimplexSolver::Closest(Vector3 v)
{
	VECTOR3_CONV(v);
	bool ret = _native->closest(VECTOR3_USE(v));
	VECTOR3_DEL(v);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTetrahedron(Vector3 p, Vector3 a, Vector3 b,
	Vector3 c, Vector3 d, SubSimplexClosestResult^ finalResult)
{
	VECTOR3_CONV(p);
	VECTOR3_CONV(a);
	VECTOR3_CONV(b);
	VECTOR3_CONV(c);
	VECTOR3_CONV(d);
	bool ret = _native->closestPtPointTetrahedron(VECTOR3_USE(p), VECTOR3_USE(a),
		VECTOR3_USE(b), VECTOR3_USE(c), VECTOR3_USE(d), *finalResult->_native);
	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	VECTOR3_DEL(d);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTriangle(Vector3 p, Vector3 a, Vector3 b,
	Vector3 c, SubSimplexClosestResult^ result)
{
	VECTOR3_CONV(p);
	VECTOR3_CONV(a);
	VECTOR3_CONV(b);
	VECTOR3_CONV(c);
	bool ret = _native->closestPtPointTriangle(VECTOR3_USE(p), VECTOR3_USE(a), VECTOR3_USE(b),
		VECTOR3_USE(c), *result->_native);
	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	return ret;
}

void VoronoiSimplexSolver::ComputePoints(Vector3 p1, Vector3 p2)
{
	VECTOR3_CONV(p1);
	VECTOR3_CONV(p2);
	_native->compute_points(VECTOR3_USE(p1), VECTOR3_USE(p2));
	VECTOR3_DEL(p1);
	VECTOR3_DEL(p2);
}

bool VoronoiSimplexSolver::EmptySimplex()
{
	return _native->emptySimplex();
}

bool VoronoiSimplexSolver::FullSimplex()
{
	return _native->fullSimplex();
}

int VoronoiSimplexSolver::GetSimplex([Out] array<Vector3>^% pBuf,
	[Out] array<Vector3>^% qBuf, [Out] array<Vector3>^% yBuf)
{
	int n = NumVertices;
	btVector3* pBufTemp = new btVector3[n];
	btVector3* qBufTemp = new btVector3[n];
	btVector3* yBufTemp = new btVector3[n];
	
	int ret = _native->getSimplex(pBufTemp, qBufTemp, yBufTemp);

	pBuf = Math::Vector3ArrayToManaged(pBufTemp, n);
	qBuf = Math::Vector3ArrayToManaged(qBufTemp, n);
	yBuf = Math::Vector3ArrayToManaged(yBufTemp, n);

	delete[] pBufTemp;
	delete[] qBufTemp;
	delete[] yBufTemp;

	return ret;
}

bool VoronoiSimplexSolver::InSimplex(Vector3 w)
{
	VECTOR3_CONV(w);
	bool ret = _native->inSimplex(VECTOR3_USE(w));
	VECTOR3_DEL(w);
	return ret;
}

btScalar VoronoiSimplexSolver::MaxVertex()
{
	return _native->maxVertex();
}

int VoronoiSimplexSolver::PointOutsideOfPlane(Vector3 p, Vector3 a, Vector3 b, Vector3 c,
	Vector3 d)
{
	VECTOR3_CONV(p);
	VECTOR3_CONV(a);
	VECTOR3_CONV(b);
	VECTOR3_CONV(c);
	VECTOR3_CONV(d);
	int ret = _native->pointOutsideOfPlane(VECTOR3_USE(p), VECTOR3_USE(a), VECTOR3_USE(b),
		VECTOR3_USE(c), VECTOR3_USE(d));
	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	VECTOR3_DEL(d);
	return ret;
}
/*
void VoronoiSimplexSolver::ReduceVertices(UsageBitfield^ usedVerts)
{
	_native->reduceVertices(*usedVerts->_native);
}
*/
void VoronoiSimplexSolver::RemoveVertex(int index)
{
	_native->removeVertex(index);
}

void VoronoiSimplexSolver::Reset()
{
	_native->reset();
}

bool VoronoiSimplexSolver::UpdateClosestVectorAndPoints()
{
	return _native->updateClosestVectorAndPoints();
}

SubSimplexClosestResult^ VoronoiSimplexSolver::CachedBC::get()
{
	return gcnew SubSimplexClosestResult(&_native->m_cachedBC);
}

Vector3 VoronoiSimplexSolver::CachedP1::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedP1);
}
void VoronoiSimplexSolver::CachedP1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedP1);
}

Vector3 VoronoiSimplexSolver::CachedP2::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedP2);
}
void VoronoiSimplexSolver::CachedP2::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedP2);
}

Vector3 VoronoiSimplexSolver::CachedV::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedV);
}
void VoronoiSimplexSolver::CachedV::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedV);
}

bool VoronoiSimplexSolver::CachedValidClosest::get()
{
	return _native->m_cachedValidClosest;
}
void VoronoiSimplexSolver::CachedValidClosest::set(bool value)
{
	_native->m_cachedValidClosest = value;
}

btScalar VoronoiSimplexSolver::EqualVertexThreshold::get()
{
	return _native->getEqualVertexThreshold();
}
void VoronoiSimplexSolver::EqualVertexThreshold::set(btScalar threshold)
{
	_native->setEqualVertexThreshold(threshold);
}

Vector3 VoronoiSimplexSolver::LastW::get()
{
	return Math::BtVector3ToVector3(&_native->m_lastW);
}
void VoronoiSimplexSolver::LastW::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_lastW);
}

bool VoronoiSimplexSolver::NeedsUpdate::get()
{
	return _native->m_needsUpdate;
}
void VoronoiSimplexSolver::NeedsUpdate::set(bool value)
{
	_native->m_needsUpdate = value;
}

int VoronoiSimplexSolver::NumVertices::get()
{
	return _native->m_numVertices;
}
void VoronoiSimplexSolver::NumVertices::set(int value)
{
	_native->m_numVertices = value;
}

Vector3Array^ VoronoiSimplexSolver::SimplexPointsP::get()
{
	return gcnew Vector3Array(_native->m_simplexPointsP, VORONOI_SIMPLEX_MAX_VERTS);
}

Vector3Array^ VoronoiSimplexSolver::SimplexPointsQ::get()
{
	return gcnew Vector3Array(_native->m_simplexPointsQ, VORONOI_SIMPLEX_MAX_VERTS);
}

Vector3Array^ VoronoiSimplexSolver::SimplexVectorW::get()
{
	return gcnew Vector3Array(_native->m_simplexVectorW, VORONOI_SIMPLEX_MAX_VERTS);
}

#endif
