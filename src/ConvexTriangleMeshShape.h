#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class ConvexTriangleMeshShape : PolyhedralConvexAabbCachingShape
	{
	private:
		StridingMeshInterface^ _stridingMeshInterface;

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
