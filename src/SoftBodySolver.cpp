#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "DefaultSoftBodySolver.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#include "SoftBodySolverVertexBuffer.h"

SoftBody::SoftBodySolver::SoftBodySolver(btSoftBodySolver* native)
{
	_native = native;
}

SoftBody::SoftBodySolver::~SoftBodySolver()
{
	this->!SoftBodySolver();
}

SoftBody::SoftBodySolver::!SoftBodySolver()
{
	delete _native;
	_native = NULL;
}

bool SoftBody::SoftBodySolver::CheckInitialized()
{
	return _native->checkInitialized();
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

void SoftBody::SoftBodySolver::PredictMotion(float solverdt)
{
	_native->predictMotion(solverdt);
}

void SoftBody::SoftBodySolver::ProcessCollision(SoftBody^ softBody, CollisionObjectWrapper^ collisionObjectWrapper)
{
	_native->processCollision((btSoftBody*)softBody->_native, collisionObjectWrapper->_native);
}

void SoftBody::SoftBodySolver::ProcessCollision(SoftBody^ softBody, SoftBody^ otherSoftBody)
{
	_native->processCollision((btSoftBody*)softBody->_native, (btSoftBody*)otherSoftBody->_native);
}

void SoftBody::SoftBodySolver::SolveConstraints(float solverdt)
{
	_native->solveConstraints(solverdt);
}

void SoftBody::SoftBodySolver::UpdateSoftBodies()
{
	_native->updateSoftBodies();
}

int SoftBody::SoftBodySolver::NumberOfPositionIterations::get()
{
	return _native->getNumberOfPositionIterations();
}
void SoftBody::SoftBodySolver::NumberOfPositionIterations::set(int iterations)
{
	_native->setNumberOfPositionIterations(iterations);
}

int SoftBody::SoftBodySolver::NumberOfVelocityIterations::get()
{
	return _native->getNumberOfVelocityIterations();
}
void SoftBody::SoftBodySolver::NumberOfVelocityIterations::set(int iterations)
{
	_native->setNumberOfVelocityIterations(iterations);
}

SolverType SoftBody::SoftBodySolver::SolverType::get()
{
	return (BulletSharp::SolverType)_native->getSolverType();
}

float SoftBody::SoftBodySolver::TimeScale::get()
{
	return _native->getTimeScale();
}


SoftBody::SoftBodySolverOutput::SoftBodySolverOutput(btSoftBodySolverOutput* native)
{
	_native = native;
}

void SoftBody::SoftBodySolverOutput::CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer)
{
	_native->copySoftBodyToVertexBuffer((btSoftBody*)softBody->_native, vertexBuffer->_native);
}

#endif
