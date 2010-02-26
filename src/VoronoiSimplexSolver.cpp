#include "StdAfx.h"

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


VoronoiSimplexSolver::VoronoiSimplexSolver()
{
	_solver = new btVoronoiSimplexSolver();
}

void VoronoiSimplexSolver::AddVertex(Vector3 w, Vector3 p, Vector3 q)
{
	UnmanagedPointer->addVertex(*Math::Vector3ToBtVec3(w),
		*Math::Vector3ToBtVec3(p), *Math::Vector3ToBtVec3(q));
}

void VoronoiSimplexSolver::BackupClosest(Vector3 v)
{
	UnmanagedPointer->backup_closest(*Math::Vector3ToBtVec3(v));
}

bool VoronoiSimplexSolver::Closest(Vector3 v)
{
	return UnmanagedPointer->closest(*Math::Vector3ToBtVec3(v));
}

bool VoronoiSimplexSolver::ClosestPtPointTetrahedron(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d,
	[Out] SubSimplexClosestResult^% finalResult)
{
	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult;
	bool ret = UnmanagedPointer->closestPtPointTetrahedron(*Math::Vector3ToBtVec3(p),
		*Math::Vector3ToBtVec3(a), *Math::Vector3ToBtVec3(b),
		*Math::Vector3ToBtVec3(c), *Math::Vector3ToBtVec3(c),
		*tempResult
	);
	finalResult = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTriangle(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c,
	[Out] SubSimplexClosestResult^% result)
{
	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult;
	bool ret = UnmanagedPointer->closestPtPointTriangle(*Math::Vector3ToBtVec3(p),
		*Math::Vector3ToBtVec3(a), *Math::Vector3ToBtVec3(b),
		*Math::Vector3ToBtVec3(c), *tempResult
	);
	result = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

void VoronoiSimplexSolver::ComputePoints(Vector3 p1, Vector3 p2)
{
	UnmanagedPointer->compute_points(*Math::Vector3ToBtVec3(p1), *Math::Vector3ToBtVec3(p2));
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
	int i = NumVertices;
	pBuf = gcnew array<Vector3>(i);
	qBuf = gcnew array<Vector3>(i);
	yBuf = gcnew array<Vector3>(i);
	btVector3* pBufTemp = new btVector3[i];
	btVector3* qBufTemp = new btVector3[i];
	btVector3* yBufTemp = new btVector3[i];
	
	int ret = UnmanagedPointer->getSimplex(pBufTemp, qBufTemp, yBufTemp);

	int j;
	for (j=0; j<i; j++)
	{
		pBuf[j] = Math::BtVec3ToVector3(&pBufTemp[j]);
		qBuf[j] = Math::BtVec3ToVector3(&qBufTemp[j]);
		yBuf[j] = Math::BtVec3ToVector3(&yBufTemp[j]);
	}

	delete[] pBufTemp;
	delete[] qBufTemp;
	delete[] yBufTemp;

	return ret;
}

bool VoronoiSimplexSolver::InSimplex(Vector3 w)
{
	return UnmanagedPointer->inSimplex(*Math::Vector3ToBtVec3(w));
}

btScalar VoronoiSimplexSolver::MaxVertex()
{
	return UnmanagedPointer->maxVertex();
}

int VoronoiSimplexSolver::PointOutsideOfPlane(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
	return UnmanagedPointer->pointOutsideOfPlane(*Math::Vector3ToBtVec3(p),
		*Math::Vector3ToBtVec3(a), *Math::Vector3ToBtVec3(b),
		*Math::Vector3ToBtVec3(c), *Math::Vector3ToBtVec3(d)
	);
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
