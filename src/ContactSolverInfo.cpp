#include "StdAfx.h"

//#ifndef DISABLE_CONSTRAINTS

#include "ContactSolverInfo.h"

ContactSolverInfoData::ContactSolverInfoData(btContactSolverInfoData* infoData)
{
	_infoData = infoData;
}

ContactSolverInfoData::ContactSolverInfoData()
{
	_infoData = new btContactSolverInfoData();
}

btScalar ContactSolverInfoData::Erp::get()
{
	return _infoData->m_erp;
}
void ContactSolverInfoData::Erp::set(btScalar value)
{
	_infoData->m_erp = value;
}

btScalar ContactSolverInfoData::Erp2::get()
{
	return _infoData->m_erp2;
}
void ContactSolverInfoData::Erp2::set(btScalar value)
{
	_infoData->m_erp2 = value;
}

btScalar ContactSolverInfoData::Damping::get()
{
	return _infoData->m_damping;
}
void ContactSolverInfoData::Damping::set(btScalar value)
{
	_infoData->m_damping = value;
}

btScalar ContactSolverInfoData::Friction::get()
{
	return _infoData->m_friction;
}
void ContactSolverInfoData::Friction::set(btScalar value)
{
	_infoData->m_friction = value;
}

btScalar ContactSolverInfoData::GlobalCfm::get()
{
	return _infoData->m_globalCfm;
}
void ContactSolverInfoData::GlobalCfm::set(btScalar value)
{
	_infoData->m_globalCfm = value;
}

btScalar ContactSolverInfoData::LinearSlop::get()
{
	return _infoData->m_linearSlop;
}
void ContactSolverInfoData::LinearSlop::set(btScalar value)
{
	_infoData->m_linearSlop = value;
}

btScalar ContactSolverInfoData::MaxErrorReduction::get()
{
	return _infoData->m_maxErrorReduction;
}
void ContactSolverInfoData::MaxErrorReduction::set(btScalar value)
{
	_infoData->m_maxErrorReduction = value;
}

int ContactSolverInfoData::MinimumSolverBatchSize::get()
{
	return _infoData->m_minimumSolverBatchSize;
}
void ContactSolverInfoData::MinimumSolverBatchSize::set(int value)
{
	_infoData->m_minimumSolverBatchSize = value;
}

int ContactSolverInfoData::NumIterations::get()
{
	return _infoData->m_numIterations;
}
void ContactSolverInfoData::NumIterations::set(int value)
{
	_infoData->m_numIterations = value;
}

int ContactSolverInfoData::RestingContactRestitutionThreshold::get()
{
	return _infoData->m_restingContactRestitutionThreshold;
}
void ContactSolverInfoData::RestingContactRestitutionThreshold::set(int value)
{
	_infoData->m_restingContactRestitutionThreshold = value;
}

btScalar ContactSolverInfoData::Restitution::get()
{
	return _infoData->m_restitution;
}
void ContactSolverInfoData::Restitution::set(btScalar value)
{
	_infoData->m_restitution = value;
}

SolverModes ContactSolverInfoData::SolverMode::get()
{
	return (SolverModes)_infoData->m_solverMode;
}
void ContactSolverInfoData::SolverMode::set(SolverModes value)
{
	_infoData->m_solverMode = (int)value;
}

btScalar ContactSolverInfoData::Sor::get()
{
	return _infoData->m_sor;
}
void ContactSolverInfoData::Sor::set(btScalar value)
{
	_infoData->m_sor = value;
}

int ContactSolverInfoData::SplitImpulse::get()
{
	return _infoData->m_splitImpulse;
}
void ContactSolverInfoData::SplitImpulse::set(int value)
{
	_infoData->m_splitImpulse = value;
}

btScalar ContactSolverInfoData::SplitImpulsePenetrationThreshold::get()
{
	return _infoData->m_splitImpulsePenetrationThreshold;
}
void ContactSolverInfoData::SplitImpulsePenetrationThreshold::set(btScalar value)
{
	_infoData->m_splitImpulsePenetrationThreshold = value;
}

btScalar ContactSolverInfoData::Tau::get()
{
	return _infoData->m_tau;
}
void ContactSolverInfoData::Tau::set(btScalar value)
{
	_infoData->m_tau = value;
}

btScalar ContactSolverInfoData::TimeStep::get()
{
	return _infoData->m_timeStep;
}
void ContactSolverInfoData::TimeStep::set(btScalar value)
{
	_infoData->m_timeStep = value;
}

btScalar ContactSolverInfoData::WarmstartingFactor::get()
{
	return _infoData->m_warmstartingFactor;
}
void ContactSolverInfoData::WarmstartingFactor::set(btScalar value)
{
	_infoData->m_warmstartingFactor = value;
}

btContactSolverInfoData* ContactSolverInfoData::UnmanagedPointer::get()
{
	return _infoData;
}
void ContactSolverInfoData::UnmanagedPointer::set(btContactSolverInfoData* value)
{
	_infoData = value;
}

ContactSolverInfo::ContactSolverInfo(btContactSolverInfo *info)
: ContactSolverInfoData(info)
{
}

ContactSolverInfo::ContactSolverInfo()
: ContactSolverInfoData(new btContactSolverInfo())
{
}

btContactSolverInfo* ContactSolverInfo::UnmanagedPointer::get()
{
	return (btContactSolverInfo*)ContactSolverInfoData::UnmanagedPointer;
}

//#endif
