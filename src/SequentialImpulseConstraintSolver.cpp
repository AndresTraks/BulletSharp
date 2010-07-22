#include "StdAfx.h"

#include "SequentialImpulseConstraintSolver.h"

SequentialImpulseConstraintSolver::SequentialImpulseConstraintSolver(btSequentialImpulseConstraintSolver* solver)
: ConstraintSolver(solver)
{
}

SequentialImpulseConstraintSolver::SequentialImpulseConstraintSolver()
: ConstraintSolver(new btSequentialImpulseConstraintSolver())
{
}

#ifndef DISABLE_CONSTRAINTS

unsigned long SequentialImpulseConstraintSolver::Rand2()
{
	return UnmanagedPointer->btRand2();
}

int SequentialImpulseConstraintSolver::RandInt2(int n)
{
	return UnmanagedPointer->btRandInt2(n);
}

unsigned long SequentialImpulseConstraintSolver::RandSeed::get()
{
	return UnmanagedPointer->getRandSeed();
}

void SequentialImpulseConstraintSolver::RandSeed::set(unsigned long value)
{
	UnmanagedPointer->setRandSeed(value);
}

btSequentialImpulseConstraintSolver* SequentialImpulseConstraintSolver::UnmanagedPointer::get()
{
	return (btSequentialImpulseConstraintSolver*)ConstraintSolver::UnmanagedPointer;
}

#endif
