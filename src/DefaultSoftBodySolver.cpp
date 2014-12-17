#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "DefaultSoftBodySolver.h"
#include "SoftBody.h"
#include "SoftBodySolverVertexBuffer.h"

#define Native static_cast<btDefaultSoftBodySolver*>(_native)

SoftBody::DefaultSoftBodySolver::DefaultSoftBodySolver()
	: SoftBodySolver(new btDefaultSoftBodySolver())
{
}

void SoftBody::DefaultSoftBodySolver::CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer)
{
	Native->copySoftBodyToVertexBuffer((btSoftBody*)softBody->_native, vertexBuffer->_native);
}

#endif
