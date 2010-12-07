#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

MinkowskiSumShape::MinkowskiSumShape(btMinkowskiSumShape* shape)
: ConvexInternalShape(shape)
{
}

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
: ConvexInternalShape(new btMinkowskiSumShape(shapeA->UnmanagedPointer, shapeB->UnmanagedPointer))
{
	_shapeA = shapeA;
	_shapeB = shapeB;
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	btConvexShape* shapeA = (btConvexShape*)UnmanagedPointer->getShapeA();
	ReturnCachedObjectUpcastNullableCastTo(CollisionShape, ConvexShape, _shapeA, shapeA);
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	btConvexShape* shapeB = (btConvexShape*)UnmanagedPointer->getShapeB();
	ReturnCachedObjectUpcastNullableCastTo(CollisionShape, ConvexShape, _shapeB, shapeB);
}

Matrix MinkowskiSumShape::TransformA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getTransformA());
}
void MinkowskiSumShape::TransformA::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	UnmanagedPointer->setTransformA(*valueTemp);
	delete valueTemp;
}

Matrix MinkowskiSumShape::TransformB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->GetTransformB());
}
void MinkowskiSumShape::TransformB::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	UnmanagedPointer->setTransformB(*valueTemp);
	delete valueTemp;
}

btMinkowskiSumShape* MinkowskiSumShape::UnmanagedPointer::get()
{
	return (btMinkowskiSumShape*)ConvexInternalShape::UnmanagedPointer;
}

#endif
