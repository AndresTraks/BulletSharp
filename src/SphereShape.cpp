#include "StdAfx.h"

#include "SphereShape.h"

SphereShape::SphereShape(btScalar radius)
: ConvexInternalShape(new btSphereShape(radius))
{
}
