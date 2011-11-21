#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	ref class ConvexPolyhedron;

	public ref class PolyhedralConvexShape abstract : ConvexInternalShape
	{
	internal:
		PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape);

	private:
		ConvexPolyhedron^ _convexPolyhedron;

	public:
		void GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB);
		void GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index);
		void GetVertex(int index, [Out] Vector3% vertex);
		bool InitializePolyhedralFeatures();
		bool IsInside(Vector3 point, btScalar tolerance);

#ifndef DISABLE_UNCOMMON
		property ConvexPolyhedron^ ConvexPolyhedron
		{
			BulletSharp::ConvexPolyhedron^ get();
		}
#endif

		property int EdgeCount
		{
			int get();
		}

		property int PlaneCount
		{
			int get();
		}

		property int VertexCount
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
