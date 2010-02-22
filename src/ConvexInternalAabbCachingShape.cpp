#include "StdAfx.h"

#include "ConvexInternalAabbCachingShape.h"

using namespace BulletSharp;

ConvexInternalAabbCachingShape::ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape)
: BulletSharp::ConvexInternalShape(convexInternalAabbCachingShape)
{
}
