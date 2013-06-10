#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "VoronoiSimplexSolver.h"

SubSimplexClosestResult::SubSimplexClosestResult(btSubSimplexClosestResult* result)
{
	_native = result;
}

bool SubSimplexClosestResult::IsValid()
{
	return _native->isValid();
}

void SubSimplexClosestResult::Reset()
{
	_native->reset();
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c, btScalar	d)
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


#ifdef NO_VIRTUAL_INTERFACE
VoronoiSimplexSolver::VoronoiSimplexSolver(btVoronoiSimplexSolver* solver)
{
	_native = solver;
}

VoronoiSimplexSolver::VoronoiSimplexSolver()
{
	_native = new btVoronoiSimplexSolver();
}

VoronoiSimplexSolver::~VoronoiSimplexSolver()
{
	this->!SimplexSolverInterface();
}

VoronoiSimplexSolver::!VoronoiSimplexSolver()
{
	delete _native;
	_native = NULL;
}

bool VoronoiSimplexSolver::IsDisposed::get()
{
	return (_native == NULL);
}
#else
VoronoiSimplexSolver::VoronoiSimplexSolver(btVoronoiSimplexSolver* solver)
: SimplexSolverInterface(solver)
{
}

VoronoiSimplexSolver::VoronoiSimplexSolver()
: SimplexSolverInterface(new btVoronoiSimplexSolver())
{
}
#endif

void VoronoiSimplexSolver::AddVertex(Vector3 w, Vector3 p, Vector3 q)
{
	VECTOR3_DEF(w);
	VECTOR3_DEF(p);
	VECTOR3_DEF(q);

	_native->addVertex(VECTOR3_USE(w), VECTOR3_USE(p), VECTOR3_USE(q));

	VECTOR3_DEL(w);
	VECTOR3_DEL(p);
	VECTOR3_DEL(q);
}

void VoronoiSimplexSolver::BackupClosest(Vector3 v)
{
	VECTOR3_DEF(v);
	_native->backup_closest(VECTOR3_USE(v));
	VECTOR3_DEL(v);
}

bool VoronoiSimplexSolver::Closest(Vector3 v)
{
	VECTOR3_DEF(v);
	bool ret = _native->closest(VECTOR3_USE(v));
	VECTOR3_DEL(v);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTetrahedron(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d, [Out] SubSimplexClosestResult^% finalResult)
{
	VECTOR3_DEF(p);
	VECTOR3_DEF(a);
	VECTOR3_DEF(b);
	VECTOR3_DEF(c);
	VECTOR3_DEF(d);

	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult();
	bool ret = _native->closestPtPointTetrahedron(VECTOR3_USE(p),
		VECTOR3_USE(a), VECTOR3_USE(b), VECTOR3_USE(c), VECTOR3_USE(d), *tempResult);

	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	VECTOR3_DEL(d);

	finalResult = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTriangle(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, [Out] SubSimplexClosestResult^% result)
{
	VECTOR3_DEF(p);
	VECTOR3_DEF(a);
	VECTOR3_DEF(b);
	VECTOR3_DEF(c);

	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult;
	bool ret = _native->closestPtPointTriangle(VECTOR3_USE(p),
		VECTOR3_USE(a), VECTOR3_USE(b), VECTOR3_USE(c), *tempResult);
	
	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);

	result = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

void VoronoiSimplexSolver::ComputePoints(Vector3 p1, Vector3 p2)
{
	VECTOR3_DEF(p1);
	VECTOR3_DEF(p2);

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
	VECTOR3_DEF(w);
	bool ret = _native->inSimplex(VECTOR3_USE(w));
	VECTOR3_DEL(w);
	return ret;
}

btScalar VoronoiSimplexSolver::MaxVertex()
{
	return _native->maxVertex();
}

int VoronoiSimplexSolver::PointOutsideOfPlane(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
	VECTOR3_DEF(p);
	VECTOR3_DEF(a);
	VECTOR3_DEF(b);
	VECTOR3_DEF(c);
	VECTOR3_DEF(d);

	int ret = _native->pointOutsideOfPlane(VECTOR3_USE(p),
		VECTOR3_USE(a), VECTOR3_USE(b), VECTOR3_USE(c), VECTOR3_USE(d));

	VECTOR3_DEL(p);
	VECTOR3_DEL(a);
	VECTOR3_DEL(b);
	VECTOR3_DEL(c);
	VECTOR3_DEL(d);

	return ret;
}

//void VoronoiSimplexSolver::ReduceVertices(UsageBitfield^ UsedVerts)
//{
//	_native->reduceVertices(UsedVerts->_native);
//}

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

int VoronoiSimplexSolver::NumVertices::get()
{
	return _native->numVertices();
}

#endif
