#include "StdAfx.h"

#ifndef DISABLE_GIMPACT
#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionAlgorithm.h"
#include "CollisionDispatcher.h"
#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "ConcaveShape.h"
#include "GImpactCollisionAlgorithm.h"
#include "GImpactShape.h"
#include "ManifoldResult.h"

GImpactCollisionAlgorithm::CreateFunc::CreateFunc(btGImpactCollisionAlgorithm::CreateFunc* native)
	: CollisionAlgorithmCreateFunc(native, true)
{
}

GImpactCollisionAlgorithm::CreateFunc::CreateFunc()
	: CollisionAlgorithmCreateFunc(new btGImpactCollisionAlgorithm::CreateFunc(), false)
{
}


#define Native static_cast<btGImpactCollisionAlgorithm*>(_native)

GImpactCollisionAlgorithm::GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* native)
	: ActivatingCollisionAlgorithm(native)
{
}

GImpactCollisionAlgorithm::GImpactCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
	: ActivatingCollisionAlgorithm(new btGImpactCollisionAlgorithm(*ci->_native, body0Wrap->_native,
		body1Wrap->_native))
{
}

void GImpactCollisionAlgorithm::GImpactVsCompoundShape(CollisionObjectWrapper^ body0Wrap,
	CollisionObjectWrapper^ body1Wrap, GImpactShapeInterface^ shape0, CompoundShape^ shape1,
	bool swapped)
{
	Native->gimpact_vs_compoundshape(body0Wrap->_native, body1Wrap->_native, (btGImpactShapeInterface*)shape0->_native,
		(btCompoundShape*)shape1->_native, swapped);
}

void GImpactCollisionAlgorithm::GImpactVsConcave(CollisionObjectWrapper^ body0Wrap,
	CollisionObjectWrapper^ body1Wrap, GImpactShapeInterface^ shape0, ConcaveShape^ shape1,
	bool swapped)
{
	Native->gimpact_vs_concave(body0Wrap->_native, body1Wrap->_native, (btGImpactShapeInterface*)shape0->_native,
		(btConcaveShape*)shape1->_native, swapped);
}

void GImpactCollisionAlgorithm::GImpactVsGImpact(CollisionObjectWrapper^ body0Wrap,
	CollisionObjectWrapper^ body1Wrap, GImpactShapeInterface^ shape0, GImpactShapeInterface^ shape1)
{
	Native->gimpact_vs_gimpact(body0Wrap->_native, body1Wrap->_native, (btGImpactShapeInterface*)shape0->_native,
		(btGImpactShapeInterface*)shape1->_native);
}

void GImpactCollisionAlgorithm::GImpactVsShape(CollisionObjectWrapper^ body0Wrap,
	CollisionObjectWrapper^ body1Wrap, GImpactShapeInterface^ shape0, CollisionShape^ shape1,
	bool swapped)
{
	Native->gimpact_vs_shape(body0Wrap->_native, body1Wrap->_native, (btGImpactShapeInterface*)shape0->_native,
		shape1->_native, swapped);
}
/*
ManifoldResult^ GImpactCollisionAlgorithm::InternalGetResultOut()
{
	return gcnew ManifoldResult(Native->internalGetResultOut(), false);
}
*/
void GImpactCollisionAlgorithm::RegisterAlgorithm(CollisionDispatcher^ dispatcher)
{
	btGImpactCollisionAlgorithm::registerAlgorithm((btCollisionDispatcher*)dispatcher->_native);
}

int GImpactCollisionAlgorithm::Face0::get()
{
	return Native->getFace0();
}
void GImpactCollisionAlgorithm::Face0::set(int value)
{
	Native->setFace0(value);
}

int GImpactCollisionAlgorithm::Face1::get()
{
	return Native->getFace1();
}
void GImpactCollisionAlgorithm::Face1::set(int value)
{
	Native->setFace1(value);
}

int GImpactCollisionAlgorithm::Part0::get()
{
	return Native->getPart0();
}
void GImpactCollisionAlgorithm::Part0::set(int value)
{
	Native->setPart0(value);
}

int GImpactCollisionAlgorithm::Part1::get()
{
	return Native->getPart1();
}
void GImpactCollisionAlgorithm::Part1::set(int value)
{
	Native->setPart1(value);
}

#endif
#endif
