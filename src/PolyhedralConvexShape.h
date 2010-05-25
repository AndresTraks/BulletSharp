#pragma once

// Fully implemented as of 25 May 2010

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class PolyhedralConvexShape abstract : ConvexInternalShape
	{
	internal:
		PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape);

	public:
		void GetEdge(int i, [Out] Vector3% pa, [Out] Vector3% pb);
		void GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int i);
		void GetVertex(int i, [Out] Vector3% vtx);
		bool IsInside(Vector3 pt, btScalar tolerance);

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

	internal:
		property btPolyhedralConvexShape* UnmanagedPointer
		{
			btPolyhedralConvexShape* get();
		}
	};

	public ref class PolyhedralConvexAabbCachingShape : PolyhedralConvexShape
	{
	internal:
		PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape* shape);

		void GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax, btScalar margin);
		void RecalcLocalAabb();

	internal:
		property btPolyhedralConvexAabbCachingShape* UnmanagedPointer
		{
			btPolyhedralConvexAabbCachingShape* get();
		}
	};
};
