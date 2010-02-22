#include "StdAfx.h"

#include "ConvexInternalShape.h"

using namespace BulletSharp;

ConvexInternalShape::ConvexInternalShape(btConvexInternalShape* convexInternalShape)
: BulletSharp::ConvexShape(convexInternalShape)
{
}
