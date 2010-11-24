#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED
#ifndef DISABLE_SOFTBODY
#ifdef __OPENCL_CL_H

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
#endif
