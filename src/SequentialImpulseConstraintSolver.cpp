#include "StdAfx.h"

#include "SequentialImpulseConstraintSolver.h"

#define Native static_cast<btSequentialImpulseConstraintSolver*>(_native)

SequentialImpulseConstraintSolver::SequentialImpulseConstraintSolver(btSequentialImpulseConstraintSolver* native)
	: ConstraintSolver(native)
{
}

SequentialImpulseConstraintSolver::SequentialImpulseConstraintSolver()
	: ConstraintSolver(ALIGNED_NEW(btSequentialImpulseConstraintSolver)())
{
}

#ifndef DISABLE_CONSTRAINTS

unsigned long SequentialImpulseConstraintSolver::Rand2()
{
	return Native->btRand2();
}

int SequentialImpulseConstraintSolver::RandInt2(int n)
{
	return Native->btRandInt2(n);
}

unsigned long SequentialImpulseConstraintSolver::RandSeed::get()
{
	return Native->getRandSeed();
}
void SequentialImpulseConstraintSolver::RandSeed::set(unsigned long seed)
{
	Native->setRandSeed(seed);
}

#endif
