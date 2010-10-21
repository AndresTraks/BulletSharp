#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED
#ifndef DISABLE_SOFTBODY

#pragma managed(push, off)
#include <BulletMultiThreaded/GpuSoftBodySolvers/CPU/btSoftBodySolver_CPU.h>
#pragma managed(pop)

#include "SoftBodySolverCpu.h"

using namespace BulletSharp::MultiThreaded;

CpuSoftBodySolver::CpuSoftBodySolver()
: SoftBodySolver(new btCPUSoftBodySolver())
{
}

btCPUSoftBodySolver* CpuSoftBodySolver::UnmanagedPointer::get()
{
	return (btCPUSoftBodySolver*)SoftBodySolver::UnmanagedPointer;
}

#endif
#endif
