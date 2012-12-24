#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

#define Native static_cast<btMinkowskiSumShape*>(_native)

MinkowskiSumShape::MinkowskiSumShape(btMinkowskiSumShape* shape)
: ConvexInternalShape(shape)
{
}

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
: ConvexInternalShape(new btMinkowskiSumShape((btConvexShape*)shapeA->_native, (btConvexShape*)shapeB->_native))
{
	_shapeA = shapeA;
	_shapeB = shapeB;
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	btConvexShape* shapeA = (btConvexShape*)Native->getShapeA();
	ReturnCachedObjectCast(ConvexShape, _shapeA, shapeA);
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	btConvexShape* shapeB = (btConvexShape*)Native->getShapeB();
	ReturnCachedObjectCast(ConvexShape, _shapeB, shapeB);
}

Matrix MinkowskiSumShape::TransformA::get()
{
	return Math::BtTransformToMatrix(&Native->getTransformA());
}
void MinkowskiSumShape::TransformA::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	Native->setTransformA(*valueTemp);
	ALIGNED_FREE(valueTemp);
}

Matrix MinkowskiSumShape::TransformB::get()
{
	return Math::BtTransformToMatrix(&Native->GetTransformB());
}
void MinkowskiSumShape::TransformB::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	Native->setTransformB(*valueTemp);
	ALIGNED_FREE(valueTemp);
}

#endif
