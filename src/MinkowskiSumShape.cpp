#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

#define Native static_cast<btMinkowskiSumShape*>(_native)

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
	: ConvexInternalShape(new btMinkowskiSumShape((btConvexShape*)shapeA->_native,
		(btConvexShape*)shapeB->_native))
{
	_shapeA = shapeA;
	_shapeB = shapeB;
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	if (_shapeA == nullptr)
	{
		return static_cast<ConvexShape^>(CollisionShape::GetManaged((btCollisionShape*)Native->getShapeA()));
	}
	return _shapeA;
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	if (_shapeB == nullptr)
	{
		return static_cast<ConvexShape^>(CollisionShape::GetManaged((btCollisionShape*)Native->getShapeB()));
	}
	return _shapeB;
}

Matrix MinkowskiSumShape::TransformA::get()
{
	return Math::BtTransformToMatrix(&Native->getTransformA());
}
void MinkowskiSumShape::TransformA::set(Matrix transA)
{
	TRANSFORM_CONV(transA);
	Native->setTransformA(TRANSFORM_USE(transA));
	TRANSFORM_DEL(transA);
}

Matrix MinkowskiSumShape::TransformB::get()
{
	return Math::BtTransformToMatrix(&Native->GetTransformB());
}
void MinkowskiSumShape::TransformB::set(Matrix transB)
{
	TRANSFORM_CONV(transB);
	Native->setTransformB(TRANSFORM_USE(transB));
	TRANSFORM_DEL(transB);
}

#endif
