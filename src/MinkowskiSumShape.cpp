#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

#define Unmanaged static_cast<btMinkowskiSumShape*>(_unmanaged)

MinkowskiSumShape::MinkowskiSumShape(btMinkowskiSumShape* shape)
: ConvexInternalShape(shape)
{
}

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
: ConvexInternalShape(new btMinkowskiSumShape((btConvexShape*)shapeA->_unmanaged, (btConvexShape*)shapeB->_unmanaged))
{
	_shapeA = shapeA;
	_shapeB = shapeB;
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	btConvexShape* shapeA = (btConvexShape*)Unmanaged->getShapeA();
	ReturnCachedObjectUpcastNullableCastTo(CollisionShape, ConvexShape, _shapeA, shapeA);
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	btConvexShape* shapeB = (btConvexShape*)Unmanaged->getShapeB();
	ReturnCachedObjectUpcastNullableCastTo(CollisionShape, ConvexShape, _shapeB, shapeB);
}

Matrix MinkowskiSumShape::TransformA::get()
{
	return Math::BtTransformToMatrix(&Unmanaged->getTransformA());
}
void MinkowskiSumShape::TransformA::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	Unmanaged->setTransformA(*valueTemp);
	delete valueTemp;
}

Matrix MinkowskiSumShape::TransformB::get()
{
	return Math::BtTransformToMatrix(&Unmanaged->GetTransformB());
}
void MinkowskiSumShape::TransformB::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	Unmanaged->setTransformB(*valueTemp);
	delete valueTemp;
}

#endif
