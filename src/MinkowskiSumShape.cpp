#include "StdAfx.h"

#include "ConvexShape.h"
#include "MinkowskiSumShape.h"

MinkowskiSumShape::MinkowskiSumShape(btMinkowskiSumShape* shape)
: ConvexInternalShape(shape)
{
}

MinkowskiSumShape::MinkowskiSumShape(ConvexShape^ shapeA, ConvexShape^ shapeB)
: ConvexInternalShape(new btMinkowskiSumShape(shapeA->UnmanagedPointer, shapeB->UnmanagedPointer))
{
}

ConvexShape^ MinkowskiSumShape::ShapeA::get()
{
	return gcnew ConvexShape((btConvexShape*)UnmanagedPointer->getShapeA());
}

ConvexShape^ MinkowskiSumShape::ShapeB::get()
{
	return gcnew ConvexShape((btConvexShape*)UnmanagedPointer->getShapeB());
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
