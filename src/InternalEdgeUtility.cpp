#include "StdAfx.h"

#ifndef DISABLE_INTERNAL_EDGE_UTILITY

#include "BvhTriangleMeshShape.h"
#include "CollisionObject.h"
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
	btGenerateInternalEdgeInfo(trimeshShape->UnmanagedPointer, triangleInfoMap->UnmanagedPointer);
}

void InternalEdgeUtility::AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObject^ trimeshColObj0, CollisionObject^ otherColObj1,
	int partId0, int index0, InternalEdgeAdjustFlags normalAdjustFlags)
{
	throw gcnew NotImplementedException();
	/* btAdjustInternalEdgeContacts(*cp->UnmanagedPointer, trimeshColObj0->UnmanagedPointer, otherColObj1->UnmanagedPointer,
		partId0, index0, (int)normalAdjustFlags); */
}

void InternalEdgeUtility::AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObject^ trimeshColObj0, CollisionObject^ otherColObj1,
	int partId0, int index0)
{
	throw gcnew NotImplementedException();
	/* btAdjustInternalEdgeContacts(*cp->UnmanagedPointer, trimeshColObj0->UnmanagedPointer, otherColObj1->UnmanagedPointer,
		partId0, index0); */
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
