#pragma once

// Fully implemented as of 29 May 2010

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class TriangleMeshShape : ConcaveShape
	{
	internal:
		TriangleMeshShape(btTriangleMeshShape* shape);

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

	internal:
		property btTriangleMeshShape* UnmanagedPointer
		{
			btTriangleMeshShape* get() new;
		}
	};
};
