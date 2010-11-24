#include "StdAfx.h"

#if !defined(DISABLE_MULTITHREADED) & !defined(DISABLE_SOFTBODY) & defined(__OPENCL_CL_H)

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
