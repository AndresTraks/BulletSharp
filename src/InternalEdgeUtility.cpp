#include "StdAfx.h"

#ifndef DISABLE_INTERNAL_EDGE_UTILITY

#include "BvhTriangleMeshShape.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "InternalEdgeUtility.h"
#include "ManifoldPoint.h"
#include "TriangleInfoMap.h"
#ifndef DISABLE_DEBUGDRAW
#ifdef BT_INTERNAL_EDGE_DEBUG_DRAW
#include "DebugDraw.h"
#endif
#endif

void InternalEdgeUtility::GenerateInternalEdgeInfo(BvhTriangleMeshShape^ trimeshShape, TriangleInfoMap^ triangleInfoMap)
{
	btGenerateInternalEdgeInfo((btBvhTriangleMeshShape*)trimeshShape->_native, triangleInfoMap->_native);
}

void InternalEdgeUtility::AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObjectWrapper^ trimeshColObj0Wrap, CollisionObjectWrapper^ otherColObj1Wrap,
	int partId0, int index0, InternalEdgeAdjustFlags normalAdjustFlags)
{
	btAdjustInternalEdgeContacts(*cp->_native, trimeshColObj0Wrap->_native, otherColObj1Wrap->_native,
		partId0, index0, (int)normalAdjustFlags);
}

void InternalEdgeUtility::AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObjectWrapper^ trimeshColObj0Wrap, CollisionObjectWrapper^ otherColObj1Wrap,
	int partId0, int index0)
{
	btAdjustInternalEdgeContacts(*cp->_native, trimeshColObj0Wrap->_native, otherColObj1Wrap->_native,
		partId0, index0);
}

#ifndef DISABLE_DEBUGDRAW
#ifdef BT_INTERNAL_EDGE_DEBUG_DRAW
void InternalEdgeUtility::SetDebugDrawer(IDebugDraw^ debugDrawer)
{
	btSetDebugDrawer(DebugDraw::GetUnmanaged(debugDrawer));
}
#endif
#endif

#endif
