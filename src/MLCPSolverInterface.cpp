#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "MLCPSolverInterface.h"

MLCPSolverInterface::MLCPSolverInterface(btMLCPSolverInterface* native)
{
	_native = native;
}
/*
bool MLCPSolverInterface::SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi, AlignedObjectArray^ limitDependency, int numIterations, bool useSparsity)
{
	_native->solveMLCP(A->_native, b->_native, x->_native, lo->_native, hi->_native, limitDependency->_native, numIterations, useSparsity);
}

bool MLCPSolverInterface::SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi, AlignedObjectArray^ limitDependency, int numIterations)
{
	_native->solveMLCP(A->_native, b->_native, x->_native, lo->_native, hi->_native, limitDependency->_native, numIterations);
}
*/
#endif
