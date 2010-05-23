#pragma once

// Fully implemented as of 23 May 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class ConvexTriangleMeshShape : PolyhedralConvexAabbCachingShape
	{
	internal:
		ConvexTriangleMeshShape(btConvexTriangleMeshShape* meshShape);

	public:
		ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface, bool calcAabb);
		ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface);

		void CalculatePrincipalAxisTransform(Matrix principal, Vector3 inertia, btScalar volume);

		property StridingMeshInterface^ MeshInterface
		{
			StridingMeshInterface^ get();
		}

	internal:
		property btConvexTriangleMeshShape* UnmanagedPointer
		{
			btConvexTriangleMeshShape* get() new;
		}
	};
};
