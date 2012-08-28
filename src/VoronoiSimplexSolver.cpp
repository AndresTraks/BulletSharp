#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "VoronoiSimplexSolver.h"

SubSimplexClosestResult::SubSimplexClosestResult(btSubSimplexClosestResult* result)
{
	_result = result;
}

bool SubSimplexClosestResult::IsValid()
{
	return _result->isValid();
}

void SubSimplexClosestResult::Reset()
{
	_result->reset();
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c, btScalar	d)
{
	_result->setBarycentricCoordinates(a, b, c, d);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c)
{
	_result->setBarycentricCoordinates(a, b, c);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a, btScalar b)
{
	_result->setBarycentricCoordinates(a, b);
}

void SubSimplexClosestResult::SetBarycentricCoordinates(btScalar a)
{
	_result->setBarycentricCoordinates(a);
}

void SubSimplexClosestResult::SetBarycentricCoordinates()
{
	_result->setBarycentricCoordinates();
}


btSubSimplexClosestResult* SubSimplexClosestResult::UnmanagedPointer::get()
{
	return _result;
}
void SubSimplexClosestResult::UnmanagedPointer::set(btSubSimplexClosestResult* value)
{
	_result = value;
}

#ifdef NO_VIRTUAL_INTERFACE
VoronoiSimplexSolver::VoronoiSimplexSolver(btVoronoiSimplexSolver* solver)
{
	_solver = solver;
}

VoronoiSimplexSolver::VoronoiSimplexSolver()
{
	_solver = new btVoronoiSimplexSolver();
}

VoronoiSimplexSolver::~VoronoiSimplexSolver()
{
	this->!SimplexSolverInterface();
}

VoronoiSimplexSolver::!VoronoiSimplexSolver()
{
	delete _solver;
	_solver = NULL;
}

bool VoronoiSimplexSolver::IsDisposed::get()
{
	return (_solver == NULL);
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

	UnmanagedPointer->addVertex(VECTOR3_USE(w), VECTOR3_USE(p), VECTOR3_USE(q));

	VECTOR3_DEL(w);
	VECTOR3_DEL(p);
	VECTOR3_DEL(q);
}

void VoronoiSimplexSolver::BackupClosest(Vector3 v)
{
	VECTOR3_DEF(v);
	UnmanagedPointer->backup_closest(VECTOR3_USE(v));
	VECTOR3_DEL(v);
}

bool VoronoiSimplexSolver::Closest(Vector3 v)
{
	VECTOR3_DEF(v);
	bool ret = UnmanagedPointer->closest(VECTOR3_USE(v));
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
	bool ret = UnmanagedPointer->closestPtPointTetrahedron(VECTOR3_USE(p),
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
	bool ret = UnmanagedPointer->closestPtPointTriangle(VECTOR3_USE(p),
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

	UnmanagedPointer->compute_points(VECTOR3_USE(p1), VECTOR3_USE(p2));

	VECTOR3_DEL(p1);
	VECTOR3_DEL(p2);
}

bool VoronoiSimplexSolver::EmptySimplex()
{
	return UnmanagedPointer->emptySimplex();
}

bool VoronoiSimplexSolver::FullSimplex()
{
	return UnmanagedPointer->fullSimplex();
}

int VoronoiSimplexSolver::GetSimplex([Out] array<Vector3>^% pBuf,
	[Out] array<Vector3>^% qBuf, [Out] array<Vector3>^% yBuf)
{
	int n = NumVertices;
	btVector3* pBufTemp = new btVector3[n];
	btVector3* qBufTemp = new btVector3[n];
	btVector3* yBufTemp = new btVector3[n];
	
	int ret = UnmanagedPointer->getSimplex(pBufTemp, qBufTemp, yBufTemp);

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
	bool ret = UnmanagedPointer->inSimplex(VECTOR3_USE(w));
	VECTOR3_DEL(w);
	return ret;
}

btScalar VoronoiSimplexSolver::MaxVertex()
{
	return UnmanagedPointer->maxVertex();
}

int VoronoiSimplexSolver::PointOutsideOfPlane(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
	VECTOR3_DEF(p);
	VECTOR3_DEF(a);
	VECTOR3_DEF(b);
	VECTOR3_DEF(c);
	VECTOR3_DEF(d);

	int ret = UnmanagedPointer->pointOutsideOfPlane(VECTOR3_USE(p),
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
//	UnmanagedPointer->reduceVertices(UsedVerts->UnmanagedPointer);
//}

void VoronoiSimplexSolver::RemoveVertex(int index)
{
	UnmanagedPointer->removeVertex(index);
}

void VoronoiSimplexSolver::Reset()
{
	UnmanagedPointer->reset();
}

bool VoronoiSimplexSolver::UpdateClosestVectorAndPoints()
{
	return UnmanagedPointer->updateClosestVectorAndPoints();
}

int VoronoiSimplexSolver::NumVertices::get()
{
	return UnmanagedPointer->numVertices();
}

btVoronoiSimplexSolver* VoronoiSimplexSolver::UnmanagedPointer::get()
{
#ifdef NO_VIRTUAL_INTERFACE
	return _solver;
#else
	return (btVoronoiSimplexSolver*)SimplexSolverInterface::UnmanagedPointer;
#endif
}
#ifdef NO_VIRTUAL_INTERFACE
void VoronoiSimplexSolver::UnmanagedPointer::set(btVoronoiSimplexSolver* value)
{
	_solver = value;
}
#endif

#endif
