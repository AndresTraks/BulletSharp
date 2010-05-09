#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h>
#pragma managed(pop)

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
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_solver = NULL;
	
	OnDisposed( this, nullptr );
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
	btVector3* wTemp = Math::Vector3ToBtVector3(w);
	btVector3* pTemp = Math::Vector3ToBtVector3(p);
	btVector3* qTemp = Math::Vector3ToBtVector3(q);

	UnmanagedPointer->addVertex(*wTemp, *pTemp, *qTemp);

	delete wTemp;
	delete pTemp;
	delete qTemp;
}

void VoronoiSimplexSolver::BackupClosest(Vector3 v)
{
	btVector3* vTemp = Math::Vector3ToBtVector3(v);
	UnmanagedPointer->backup_closest(*vTemp);
	delete vTemp;
}

bool VoronoiSimplexSolver::Closest(Vector3 v)
{
	btVector3* vTemp = Math::Vector3ToBtVector3(v);
	bool ret = UnmanagedPointer->closest(*vTemp);
	delete vTemp;
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTetrahedron(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d, [Out] SubSimplexClosestResult^% finalResult)
{
	btVector3* aTemp = Math::Vector3ToBtVector3(a);
	btVector3* bTemp = Math::Vector3ToBtVector3(b);
	btVector3* cTemp = Math::Vector3ToBtVector3(c);
	btVector3* dTemp = Math::Vector3ToBtVector3(d);

	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult;

	bool ret = UnmanagedPointer->closestPtPointTetrahedron(*Math::Vector3ToBtVector3(p),
		*aTemp, *bTemp, *cTemp, *dTemp, *tempResult);

	delete aTemp;
	delete bTemp;
	delete cTemp;
	delete dTemp;

	finalResult = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

bool VoronoiSimplexSolver::ClosestPtPointTriangle(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, [Out] SubSimplexClosestResult^% result)
{
	btVector3* pTemp = Math::Vector3ToBtVector3(p);
	btVector3* aTemp = Math::Vector3ToBtVector3(a);
	btVector3* bTemp = Math::Vector3ToBtVector3(b);
	btVector3* cTemp = Math::Vector3ToBtVector3(c);

	btSubSimplexClosestResult* tempResult = new btSubSimplexClosestResult;
	bool ret = UnmanagedPointer->closestPtPointTriangle(*pTemp, *aTemp, *bTemp, *cTemp, *tempResult);
	
	delete pTemp;
	delete aTemp;
	delete bTemp;
	delete cTemp;

	result = gcnew SubSimplexClosestResult(tempResult);
	return ret;
}

void VoronoiSimplexSolver::ComputePoints(Vector3 p1, Vector3 p2)
{
	btVector3* p1Temp = Math::Vector3ToBtVector3(p1);
	btVector3* p2Temp = Math::Vector3ToBtVector3(p2);

	UnmanagedPointer->compute_points(*p1Temp, *p2Temp);

	delete p1Temp;
	delete p2Temp;
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
		pBuf[j] = Math::BtVector3ToVector3(&pBufTemp[j]);
		qBuf[j] = Math::BtVector3ToVector3(&qBufTemp[j]);
		yBuf[j] = Math::BtVector3ToVector3(&yBufTemp[j]);
	}

	delete[] pBufTemp;
	delete[] qBufTemp;
	delete[] yBufTemp;

	return ret;
}

bool VoronoiSimplexSolver::InSimplex(Vector3 w)
{
	return UnmanagedPointer->inSimplex(*Math::Vector3ToBtVector3(w));
}

btScalar VoronoiSimplexSolver::MaxVertex()
{
	return UnmanagedPointer->maxVertex();
}

int VoronoiSimplexSolver::PointOutsideOfPlane(Vector3 p,
	Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
	btVector3* pTemp = Math::Vector3ToBtVector3(p);
	btVector3* aTemp = Math::Vector3ToBtVector3(a);
	btVector3* bTemp = Math::Vector3ToBtVector3(b);
	btVector3* cTemp = Math::Vector3ToBtVector3(c);
	btVector3* dTemp = Math::Vector3ToBtVector3(d);

	int ret = UnmanagedPointer->pointOutsideOfPlane(*pTemp,
		*aTemp, *bTemp, *cTemp, *dTemp);

	delete pTemp;
	delete aTemp;
	delete bTemp;
	delete cTemp;
	delete dTemp;

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
