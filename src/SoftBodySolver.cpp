#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::SoftBodySolver::SoftBodySolver(btSoftBodySolver* solver)
{
	_solver = solver;
}

void SoftBody::SoftBodySolver::Optimize(AlignedSoftBodyArray^ softBodies)
{
	_solver->optimize(*softBodies->UnmanagedPointer);
}

void SoftBody::SoftBodySolver::CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer)
{
	_solver->copySoftBodyToVertexBuffer(softBody->UnmanagedPointer, vertexBuffer->UnmanagedPointer);
}

int SoftBody::SoftBodySolver::NumberOfPositionIterations::get()
{
	return _solver->getNumberOfPositionIterations();
}
void SoftBody::SoftBodySolver::NumberOfPositionIterations::set(int value)
{
	_solver->setNumberOfPositionIterations(value);
}

int SoftBody::SoftBodySolver::NumberOfVelocityIterations::get()
{
	return _solver->getNumberOfVelocityIterations();
}
void SoftBody::SoftBodySolver::NumberOfVelocityIterations::set(int value)
{
	_solver->setNumberOfVelocityIterations(value);
}

float SoftBody::SoftBodySolver::TimeScale::get()
{
	return _solver->getTimeScale();
}

btSoftBodySolver* SoftBody::SoftBodySolver::UnmanagedPointer::get()
{
	return _solver;
}
void SoftBody::SoftBodySolver::UnmanagedPointer::set(btSoftBodySolver* value)
{
	_solver = value;
}

#endif
