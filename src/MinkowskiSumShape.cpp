#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

#define Native static_cast<btMinkowskiSumShape*>(_native)

MinkowskiSumShape::MinkowskiSumShape(btMinkowskiSumShape* native)
	: ConvexInternalShape(native)
{
}

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
	: ConvexInternalShape(new btMinkowskiSumShape((btConvexShape*)shapeA->_native, (btConvexShape*)shapeB->_native))
{
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	return static_cast<ConvexShape^>(CollisionShape::GetManaged((btCollisionShape*)Native->getShapeA()));
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	return static_cast<ConvexShape^>(CollisionShape::GetManaged((btCollisionShape*)Native->getShapeB()));
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
