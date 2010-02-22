#include "StdAfx.h"

#include "CompoundShape.h"

CompoundShape::CompoundShape()
: CollisionShape(new btCompoundShape())
{
}

CompoundShape::CompoundShape(bool enableDynamicAabbTree)
: CollisionShape(new btCompoundShape(enableDynamicAabbTree))
{
}

void CompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	UnmanagedPointer->addChildShape(*Math::MatrixToBtTransform(localTransform), shape->UnmanagedPointer);
}

btCompoundShape* CompoundShape::UnmanagedPointer::get()
{
	return (btCompoundShape*)CollisionShape::UnmanagedPointer;
}
