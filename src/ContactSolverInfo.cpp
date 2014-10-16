#include "StdAfx.h"

//#ifndef DISABLE_CONSTRAINTS

#include "ContactSolverInfo.h"

ContactSolverInfoData::ContactSolverInfoData(btContactSolverInfoData* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

ContactSolverInfoData::~ContactSolverInfoData()
{
	this->!ContactSolverInfoData();
}

ContactSolverInfoData::!ContactSolverInfoData()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

ContactSolverInfoData::ContactSolverInfoData()
{
	_native = new btContactSolverInfoData();
}

btScalar ContactSolverInfoData::Damping::get()
{
	return _native->m_damping;
}
void ContactSolverInfoData::Damping::set(btScalar value)
{
	_native->m_damping = value;
}

btScalar ContactSolverInfoData::Erp::get()
{
	return _native->m_erp;
}
void ContactSolverInfoData::Erp::set(btScalar value)
{
	_native->m_erp = value;
}

btScalar ContactSolverInfoData::Erp2::get()
{
	return _native->m_erp2;
}
void ContactSolverInfoData::Erp2::set(btScalar value)
{
	_native->m_erp2 = value;
}

btScalar ContactSolverInfoData::Friction::get()
{
	return _native->m_friction;
}
void ContactSolverInfoData::Friction::set(btScalar value)
{
	_native->m_friction = value;
}

btScalar ContactSolverInfoData::GlobalCfm::get()
{
	return _native->m_globalCfm;
}
void ContactSolverInfoData::GlobalCfm::set(btScalar value)
{
	_native->m_globalCfm = value;
}

btScalar ContactSolverInfoData::LinearSlop::get()
{
	return _native->m_linearSlop;
}
void ContactSolverInfoData::LinearSlop::set(btScalar value)
{
	_native->m_linearSlop = value;
}

btScalar ContactSolverInfoData::MaxErrorReduction::get()
{
	return _native->m_maxErrorReduction;
}
void ContactSolverInfoData::MaxErrorReduction::set(btScalar value)
{
	_native->m_maxErrorReduction = value;
}

btScalar ContactSolverInfoData::MaxGyroscopicForce::get()
{
	return _native->m_maxGyroscopicForce;
}
void ContactSolverInfoData::MaxGyroscopicForce::set(btScalar value)
{
	_native->m_maxGyroscopicForce = value;
}

int ContactSolverInfoData::MinimumSolverBatchSize::get()
{
	return _native->m_minimumSolverBatchSize;
}
void ContactSolverInfoData::MinimumSolverBatchSize::set(int value)
{
	_native->m_minimumSolverBatchSize = value;
}

int ContactSolverInfoData::NumIterations::get()
{
	return _native->m_numIterations;
}
void ContactSolverInfoData::NumIterations::set(int value)
{
	_native->m_numIterations = value;
}

int ContactSolverInfoData::RestingContactRestitutionThreshold::get()
{
	return _native->m_restingContactRestitutionThreshold;
}
void ContactSolverInfoData::RestingContactRestitutionThreshold::set(int value)
{
	_native->m_restingContactRestitutionThreshold = value;
}

btScalar ContactSolverInfoData::Restitution::get()
{
	return _native->m_restitution;
}
void ContactSolverInfoData::Restitution::set(btScalar value)
{
	_native->m_restitution = value;
}

btScalar ContactSolverInfoData::SingleAxisRollingFrictionThreshold::get()
{
	return _native->m_singleAxisRollingFrictionThreshold;
}
void ContactSolverInfoData::SingleAxisRollingFrictionThreshold::set(btScalar value)
{
	_native->m_singleAxisRollingFrictionThreshold = value;
}

SolverModes ContactSolverInfoData::SolverMode::get()
{
	return (SolverModes)_native->m_solverMode;
}
void ContactSolverInfoData::SolverMode::set(SolverModes value)
{
	_native->m_solverMode = (int)value;
}

btScalar ContactSolverInfoData::Sor::get()
{
	return _native->m_sor;
}
void ContactSolverInfoData::Sor::set(btScalar value)
{
	_native->m_sor = value;
}

int ContactSolverInfoData::SplitImpulse::get()
{
	return _native->m_splitImpulse;
}
void ContactSolverInfoData::SplitImpulse::set(int value)
{
	_native->m_splitImpulse = value;
}

btScalar ContactSolverInfoData::SplitImpulsePenetrationThreshold::get()
{
	return _native->m_splitImpulsePenetrationThreshold;
}
void ContactSolverInfoData::SplitImpulsePenetrationThreshold::set(btScalar value)
{
	_native->m_splitImpulsePenetrationThreshold = value;
}

btScalar ContactSolverInfoData::SplitImpulseTurnErp::get()
{
	return _native->m_splitImpulseTurnErp;
}
void ContactSolverInfoData::SplitImpulseTurnErp::set(btScalar value)
{
	_native->m_splitImpulseTurnErp = value;
}

btScalar ContactSolverInfoData::Tau::get()
{
	return _native->m_tau;
}
void ContactSolverInfoData::Tau::set(btScalar value)
{
	_native->m_tau = value;
}

btScalar ContactSolverInfoData::TimeStep::get()
{
	return _native->m_timeStep;
}
void ContactSolverInfoData::TimeStep::set(btScalar value)
{
	_native->m_timeStep = value;
}

btScalar ContactSolverInfoData::WarmstartingFactor::get()
{
	return _native->m_warmstartingFactor;
}
void ContactSolverInfoData::WarmstartingFactor::set(btScalar value)
{
	_native->m_warmstartingFactor = value;
}


ContactSolverInfo::ContactSolverInfo(btContactSolverInfo* native, bool preventDelete)
	: ContactSolverInfoData(native, preventDelete)
{
}

ContactSolverInfo::ContactSolverInfo()
	: ContactSolverInfoData(new btContactSolverInfo(), false)
{
}

//#endif
