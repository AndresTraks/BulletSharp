#pragma once

namespace BulletSharp
{
	ref class BvhTriangleMeshShape;
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class ManifoldPoint;
	ref class TriangleInfoMap;
	interface class IDebugDraw;

	[Flags]
	public enum class InternalEdgeAdjustFlags
	{
		None = 0,
		TriangleConvexBackfaceMode = BT_TRIANGLE_CONVEX_BACKFACE_MODE,
		TriangleConcaveDoubleSided = BT_TRIANGLE_CONCAVE_DOUBLE_SIDED,
		TriangleConvexDoubleSided = BT_TRIANGLE_CONVEX_DOUBLE_SIDED
	};

	public ref class InternalEdgeUtility sealed
	{
	private:
		InternalEdgeUtility() {}

	public:
		static void GenerateInternalEdgeInfo(BvhTriangleMeshShape^ trimeshShape, TriangleInfoMap^ triangleInfoMap);
		static void AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObjectWrapper^ trimeshColObj0Wrap, CollisionObjectWrapper^ otherColObj1Wrap,
			int partId0, int index0, InternalEdgeAdjustFlags normalAdjustFlags);
		static void AdjustInternalEdgeContacts(ManifoldPoint^ cp, CollisionObjectWrapper^ trimeshColObj0Wrap, CollisionObjectWrapper^ otherColObj1Wrap,
			int partId0, int index0);
#ifndef DISABLE_DEBUGDRAW
#ifdef BT_INTERNAL_EDGE_DEBUG_DRAW
		static void SetDebugDrawer(IDebugDraw^ debugDrawer);
#endif
#endif
	};
};
