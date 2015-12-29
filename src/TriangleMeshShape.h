#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class TriangleMeshShape : ConcaveShape
	{
	protected:
		StridingMeshInterface^ _meshInterface;

	internal:
		TriangleMeshShape(btTriangleMeshShape* native);

	public:
		Vector3 LocalGetSupportingVertex(Vector3 vec);
		Vector3 LocalGetSupportingVertexWithoutMargin(Vector3 vec);
		void RecalcLocalAabb();

		property Vector3 LocalAabbMax
		{
			Vector3 get();
		}

		property Vector3 LocalAabbMin
		{
			Vector3 get();
		}

		property StridingMeshInterface^ MeshInterface
		{
			StridingMeshInterface^ get();
		}
	};
};
