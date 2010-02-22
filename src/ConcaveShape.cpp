#include "StdAfx.h"

#include "ConcaveShape.h"

ConcaveShape::ConcaveShape(btConcaveShape* concaveShape)
: CollisionShape(concaveShape)
{
}

btConcaveShape* ConcaveShape::UnmanagedPointer::get()
{
	return (btConcaveShape*)CollisionShape::UnmanagedPointer;
}
