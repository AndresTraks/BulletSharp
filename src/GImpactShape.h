#pragma once

#include "CollisionWorld.h"
#include "ConcaveShape.h"
#include "TetrahedronShape.h"
#include "TriangleCallback.h"
#ifndef DISABLE_BVH
#include "GImpactBvh.h"
#include "GImpactQuantizedBvh.h"
#endif

namespace BulletSharp
{
	ref class Aabb;
	ref class PrimitiveManagerBase;
	ref class PrimitiveTriangle;
	ref class StridingMeshInterface;
	ref class TriangleCallback;
	ref class TriangleShapeEx;

	public enum class GImpactShapeType
	{
		CompoundShape = CONST_GIMPACT_COMPOUND_SHAPE,
		TrimeshShapePart = CONST_GIMPACT_TRIMESH_SHAPE_PART,
		TrimeshShape = CONST_GIMPACT_TRIMESH_SHAPE
	};

	public ref class TetrahedronShapeEx : BU_Simplex1to4
	{
	internal:
		TetrahedronShapeEx(btTetrahedronShapeEx* shape);

	public:
		TetrahedronShapeEx();

		void SetVertices(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3);
	};

	public ref class GImpactShapeInterface : ConcaveShape
	{
	internal:
		GImpactShapeInterface(btGImpactShapeInterface* shapeInterface);

	public:
		void GetBulletTetrahedron(int prim_index, [Out] TetrahedronShapeEx^% tetrahedron);
		void GetBulletTriangle(int prim_index, TriangleShapeEx^ triangle);
		CollisionShape^ GetChildShape(int index);
		Matrix GetChildTransform(int index);
		void GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle);
		void LockChildShapes();
		void PostUpdate();
		void ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax);
		void ProcessAllTrianglesRay(TriangleCallback^ callback, Vector3 rayFrom, Vector3 rayTo);
		void RayTest(Vector3 rayFrom, Vector3 rayTo, CollisionWorld::RayResultCallback^ resultCallback);
		void SetChildTransform(int index, Matrix transform);
		void UnlockChildShapes();
		void UpdateBound();

#ifndef DISABLE_BVH
		property GImpactQuantizedBvh^ BoxSet
		{
			GImpactQuantizedBvh^ get();
		}
#endif

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
	};

	public ref class GImpactCompoundShape : GImpactShapeInterface
	{
	public:
#ifndef DISABLE_BVH
		ref class CompoundPrimitiveManager : PrimitiveManagerBase
		{
		internal:
			CompoundPrimitiveManager(btGImpactCompoundShape::CompoundPrimitiveManager* compound);

		public:
			CompoundPrimitiveManager(CompoundPrimitiveManager^ compound);
			CompoundPrimitiveManager(GImpactCompoundShape^ compoundShape);
			CompoundPrimitiveManager();

			property GImpactCompoundShape^ CompoundShape
			{
				GImpactCompoundShape^ get();
			}
		};
#endif

		GImpactCompoundShape(bool childrenHasTransform);
		GImpactCompoundShape();

		void AddChildShape(CollisionShape^ shape);
		void AddChildShape(Matrix localTransform, CollisionShape^ shape);

#ifndef DISABLE_BVH
		property CompoundPrimitiveManager^ GImpactCompoundPrimitiveManager
		{
			CompoundPrimitiveManager^ get();
		}
#endif
	};

	public ref class GImpactMeshShapePart : GImpactShapeInterface
	{
	public:
#ifndef DISABLE_BVH
		ref class TrimeshPrimitiveManager : PrimitiveManagerBase
		{
		internal:
			TrimeshPrimitiveManager(btGImpactMeshShapePart::TrimeshPrimitiveManager* manager);

		public:
			TrimeshPrimitiveManager();
			TrimeshPrimitiveManager(TrimeshPrimitiveManager^ manager);
			TrimeshPrimitiveManager(StridingMeshInterface^ meshInterface, int part);

			void GetBulletTriangle(int prim_index, TriangleShapeEx^ triangle);
			void GetIndices(int face_index, unsigned int% i0, unsigned int% i1, unsigned int% i2);
			void Lock();
			void Unlock();

			property IntPtr IndexBase
			{
				IntPtr get();
				void set(IntPtr value);
			}

			property int IndexStride
			{
				int get();
				void set(int value);
			}

			property PhyScalarType IndicesType
			{
				PhyScalarType get();
				void set(PhyScalarType value);
			}

			property int LockCount
			{
				int get();
				void set(int value);
			}

			property btScalar Margin
			{
				btScalar get();
				void set(btScalar value);
			}

			property StridingMeshInterface^ MeshInterface
			{
				StridingMeshInterface^ get();
				void set(StridingMeshInterface^ value);
			}

			property int NumFaces
			{
				int get();
				void set(int value);
			}

			property int NumVerts
			{
				int get();
				void set(int value);
			}

			property int Part
			{
				int get();
				void set(int value);
			}

			property Vector3 Scale
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property int Stride
			{
				int get();
				void set(int value);
			}

			property PhyScalarType Type
			{
				PhyScalarType get();
				void set(PhyScalarType value);
			}

			property IntPtr VertexBase
			{
				IntPtr get();
				void set(IntPtr value);
			}
		};
#endif

	internal:
		GImpactMeshShapePart(btGImpactMeshShapePart* shape);

	public:
		GImpactMeshShapePart();
		GImpactMeshShapePart(StridingMeshInterface^ meshInterface, int part);

		void GetVertex(unsigned int vertexIndex, [Out] Vector3% vertex);

		property int Part
		{
			int get();
		}

		property int VertexCount
		{
			int get();
		}

#ifndef DISABLE_BVH
		property TrimeshPrimitiveManager^ GImpactTrimeshPrimitiveManager
		{
			TrimeshPrimitiveManager^ get();
		}
#endif
	};

	public ref class GImpactMeshShape : GImpactShapeInterface
	{
	internal:
		GImpactMeshShape(btGImpactMeshShape* shape);

	public:
		GImpactMeshShape(StridingMeshInterface^ meshInterface);

		GImpactMeshShapePart^ GetMeshPart(int index);

		property StridingMeshInterface^ MeshInterface
		{
			StridingMeshInterface^ get();
		}

		property int MeshPartCount
		{
			int get();
		}
	};
};
