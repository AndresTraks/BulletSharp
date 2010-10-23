#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED
#ifndef DISABLE_SOFTBODY

#pragma managed(push, off)
#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#pragma managed(pop)

#include "SoftBodySolverOpenCL.h"

using namespace BulletSharp::MultiThreaded;

OpenCLSoftBodySolver::OpenCLSoftBodySolver(IntPtr queue, IntPtr context)
: SoftBodySolver(new btOpenCLSoftBodySolver((cl_command_queue)queue.ToPointer(), (cl_context)context.ToPointer()))
{
}

btOpenCLSoftBodySolver* OpenCLSoftBodySolver::UnmanagedPointer::get()
{
	return (btOpenCLSoftBodySolver*)SoftBodySolver::UnmanagedPointer;
}

#endif
#endif
