#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::SoftBodySolver::SoftBodySolver(btSoftBodySolver* solver)
{
	_native = solver;
}

void SoftBody::SoftBodySolver::CopyBackToSoftBodies(bool bMove)
{
	_native->copyBackToSoftBodies(bMove);
}

void SoftBody::SoftBodySolver::CopyBackToSoftBodies()
{
	_native->copyBackToSoftBodies();
}

void SoftBody::SoftBodySolver::Optimize(AlignedSoftBodyArray^ softBodies, bool forceUpdate)
{
	_native->optimize(*(btSoftBody::tSoftBodyArray*)softBodies->_native, forceUpdate);
}

void SoftBody::SoftBodySolver::Optimize(AlignedSoftBodyArray^ softBodies)
{
	_native->optimize(*(btSoftBody::tSoftBodyArray*)softBodies->_native);
}

void SoftBody::SoftBodySolver::ProcessCollision(SoftBody^ softBody, CollisionObjectWrapper^ collisionObjectWrapper)
{
	_native->processCollision((btSoftBody*)softBody->_native, collisionObjectWrapper->_native);
}

void SoftBody::SoftBodySolver::ProcessCollision(SoftBody^ softBody, SoftBody^ otherSoftBody)
{
	_native->processCollision((btSoftBody*)softBody->_native, (btSoftBody*)otherSoftBody->_native);
}

int SoftBody::SoftBodySolver::NumberOfPositionIterations::get()
{
	return _native->getNumberOfPositionIterations();
}
void SoftBody::SoftBodySolver::NumberOfPositionIterations::set(int value)
{
	_native->setNumberOfPositionIterations(value);
}

int SoftBody::SoftBodySolver::NumberOfVelocityIterations::get()
{
	return _native->getNumberOfVelocityIterations();
}
void SoftBody::SoftBodySolver::NumberOfVelocityIterations::set(int value)
{
	_native->setNumberOfVelocityIterations(value);
}

SolverType SoftBody::SoftBodySolver::SolverType::get()
{
	return (BulletSharp::SolverType)_native->getSolverType();
}

float SoftBody::SoftBodySolver::TimeScale::get()
{
	return _native->getTimeScale();
}

btSoftBodySolver* SoftBody::SoftBodySolver::UnmanagedPointer::get()
{
	return _native;
}
void SoftBody::SoftBodySolver::UnmanagedPointer::set(btSoftBodySolver* value)
{
	_native = value;
}


SoftBody::SoftBodySolverOutput::SoftBodySolverOutput(btSoftBodySolverOutput* solverOutput)
{
	_solverOutput = solverOutput;
}

void SoftBody::SoftBodySolverOutput::CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer)
{
	_solverOutput->copySoftBodyToVertexBuffer((btSoftBody*)softBody->_native, vertexBuffer->UnmanagedPointer);
}

btSoftBodySolverOutput* SoftBody::SoftBodySolverOutput::UnmanagedPointer::get()
{
	return _solverOutput;
}
void SoftBody::SoftBodySolverOutput::UnmanagedPointer::set(btSoftBodySolverOutput* value)
{
	_solverOutput = value;
}

#endif
