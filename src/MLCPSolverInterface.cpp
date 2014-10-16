#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "MlcpSolverInterface.h"

MlcpSolverInterface::MlcpSolverInterface(btMLCPSolverInterface* native)
{
	_native = native;
}

MlcpSolverInterface::~MlcpSolverInterface()
{
	this->!MlcpSolverInterface();
}

MlcpSolverInterface::!MlcpSolverInterface()
{
	delete _native;
	_native = NULL;
}
/*
bool MlcpSolverInterface::SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo,
	VectorXf^ hi, AlignedObjectArray^ limitDependency, int numIterations, bool useSparsity)
{
	return _native->solveMLCP(*A->_native, *b->_native, *x->_native, *lo->_native,
		*hi->_native, *limitDependency->_native, numIterations, useSparsity);
}

bool MlcpSolverInterface::SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo,
	VectorXf^ hi, AlignedObjectArray^ limitDependency, int numIterations)
{
	return _native->solveMLCP(*A->_native, *b->_native, *x->_native, *lo->_native,
		*hi->_native, *limitDependency->_native, numIterations);
}
*/
#endif
