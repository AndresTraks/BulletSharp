#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactShape.h>
#pragma managed(pop)

#include "CollisionWorld.h"
#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class Aabb;
	ref class PrimitiveManagerBase;
	ref class PrimitiveTriangle;
	ref class StridingMeshInterface;
	ref class TriangleShapeEx;

	public enum class GImpactShapeType
	{
		CompoundShape = CONST_GIMPACT_COMPOUND_SHAPE,
		TrimeshShapePart = CONST_GIMPACT_TRIMESH_SHAPE_PART,
		TrimeshShape = CONST_GIMPACT_TRIMESH_SHAPE
	};

	public ref class GImpactShapeInterface : ConcaveShape
	{
	internal:
		GImpactShapeInterface(btGImpactShapeInterface* shapeInterface);

	public:
		//void GetBulletTetrahedron(int prim_index, [Out] TetrahedronShapeEx^% tetrahedron);
		void GetBulletTriangle(int prim_index, [Out] TriangleShapeEx^% triangle);
		CollisionShape^ GetChildShape(int index);
		Matrix GetChildTransform(int index);
		void GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle);
		void LockChildShapes();
		void PostUpdate();
		void RayTest(Vector3 rayFrom, Vector3 rayTo, CollisionWorld::RayResultCallback^ resultCallback);
		void SetChildTransform(int index, Matrix transform);
		void UnlockChildShapes();
		void UpdateBound();

		//property GImpactBoxSet^ BoxSet
		//{
		//	GImpactBoxSet^ get();
		//}

		property bool ChildrenHasTransform
		{
			bool get();
		}

		property BulletSharp::GImpactShapeType GImpactShapeType
		{
			BulletSharp::GImpactShapeType get();
		}

		property bool HasBoxSet
		{
			bool get();
		}

		property Aabb^ LocalBox
		{
			Aabb^ get();
		}

		property bool NeedsRetrieveTetrahedrons
		{
			bool get();
		}

		property bool NeedsRetrieveTriangles
		{
			bool get();
		}

		property int NumChildShapes
		{
			int get();
		}

#ifndef DISABLE_BVH
		property PrimitiveManagerBase^ PrimitiveManager
		{
			PrimitiveManagerBase^ get();
		}
#endif

	internal:
		property btGImpactShapeInterface* UnmanagedPointer
		{
			btGImpactShapeInterface* get();
		}
	};

	public ref class GImpactMeshShape : GImpactShapeInterface
	{
	internal:
		GImpactMeshShape(btGImpactMeshShape* shape);
	public:
		GImpactMeshShape(StridingMeshInterface^ meshInterface);

		//GImpactMeshShapePart^ GetMeshPart(int index);

		property StridingMeshInterface^ MeshInterface
		{
			StridingMeshInterface^ get();
		}

		property int MeshPartCount
		{
			int get();
		}

	internal:
		property btGImpactMeshShape* UnmanagedPointer
		{
			btGImpactMeshShape* get();
		}
	};
};
