#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	ref class ConvexPolyhedron;

	public ref class PolyhedralConvexShape abstract : ConvexInternalShape
	{
	internal:
		PolyhedralConvexShape(btPolyhedralConvexShape* native);

#ifndef DISABLE_UNCOMMON
	private:
		ConvexPolyhedron^ _convexPolyhedron;
#endif

	public:
		void GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB);
		void GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index);
		void GetVertex(int index, [Out] Vector3% vertex);
		bool InitializePolyhedralFeatures(int shiftVerticesByMargin);
		bool InitializePolyhedralFeatures();
		bool IsInside(Vector3 point, btScalar tolerance);

#ifndef DISABLE_UNCOMMON
		property ConvexPolyhedron^ ConvexPolyhedron
		{
			BulletSharp::ConvexPolyhedron^ get();
		}
#endif

		property int NumEdges
		{
			int get();
		}

		property int NumPlanes
		{
			int get();
		}

		property int NumVertices
		{
			int get();
		}
	};

	public ref class PolyhedralConvexAabbCachingShape abstract : PolyhedralConvexShape
	{
	internal:
		PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape* native);

	public:
		void GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax, btScalar margin);
		void RecalcLocalAabb();
	};
};
