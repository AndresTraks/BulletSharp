#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class ConvexTriangleMeshShape : PolyhedralConvexAabbCachingShape
	{
		StridingMeshInterface^ _meshInterface;

	internal:
		ConvexTriangleMeshShape(btConvexTriangleMeshShape* native);

	public:
		ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface, bool calcAabb);
		ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface);

		void CalculatePrincipalAxisTransform(Matrix% principal, [Out] Vector3% inertia, [Out] btScalar% volume);

		property StridingMeshInterface^ MeshInterface
		{
			StridingMeshInterface^ get();
		}
	};
};
