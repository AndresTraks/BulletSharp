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

	public ref class TetrahedronShapeEx : BuSimplex1To4
	{
	internal:
		TetrahedronShapeEx(btTetrahedronShapeEx* native);

	public:
		TetrahedronShapeEx();

		void SetVertices(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3);
	};

	public ref class GImpactShapeInterface abstract : ConcaveShape
	{
#ifndef DISABLE_BVH
	protected:
		PrimitiveManagerBase^ _primitiveManagerBase;
#endif

	internal:
		GImpactShapeInterface(btGImpactShapeInterface* native);

	public:
		virtual void GetAabbRef(Matrix% t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax) override;
		virtual void GetAabb(Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax) override;
		void GetBulletTetrahedron(int primIndex, TetrahedronShapeEx^ tetrahedron);
		void GetBulletTriangle(int primIndex, TriangleShapeEx^ triangle);
		void GetChildAabb(int childIndex, Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		CollisionShape^ GetChildShape(int index);
		Matrix GetChildTransform(int index);
		void GetPrimitiveTriangle(int index, PrimitiveTriangle^ triangle);
		void LockChildShapes();
		void PostUpdate();
		void ProcessAllTrianglesRay(TriangleCallback^ callback, Vector3 rayFrom,
			Vector3 rayTo);
		void RayTest(Vector3 rayFrom, Vector3 rayTo, RayResultCallback^ resultCallback);
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
			virtual PrimitiveManagerBase^ get() abstract;
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
			CompoundPrimitiveManager(btGImpactCompoundShape::CompoundPrimitiveManager* native);

		public:
			CompoundPrimitiveManager(CompoundPrimitiveManager^ compound);
			CompoundPrimitiveManager(GImpactCompoundShape^ compoundShape);
			CompoundPrimitiveManager();

			property GImpactCompoundShape^ CompoundShape
			{
				GImpactCompoundShape^ get();
				void set(GImpactCompoundShape^ value);
			}
		};
#endif

	internal:
		GImpactCompoundShape(btGImpactCompoundShape* native);

	public:
		GImpactCompoundShape(bool childrenHasTransform);
		GImpactCompoundShape();

		void AddChildShape(Matrix localTransform, CollisionShape^ shape);
		void AddChildShape(CollisionShape^ shape);

#ifndef DISABLE_BVH
		property CompoundPrimitiveManager^ GImpactCompoundPrimitiveManager
		{
			CompoundPrimitiveManager^ get();
		}

		property PrimitiveManagerBase^ PrimitiveManager
		{
			virtual PrimitiveManagerBase^ get() override;
		}
#endif
	};

	public ref class GImpactMeshShapePart : GImpactShapeInterface
	{
	public:
#ifndef DISABLE_BVH
		ref class TrimeshPrimitiveManager : PrimitiveManagerBase
		{
			StridingMeshInterface^ _meshInterface;

		internal:
			TrimeshPrimitiveManager(btGImpactMeshShapePart::TrimeshPrimitiveManager* native);

		public:
			TrimeshPrimitiveManager(StridingMeshInterface^ meshInterface, int part);
			TrimeshPrimitiveManager(TrimeshPrimitiveManager^ manager);
			TrimeshPrimitiveManager();

			void GetBulletTriangle(int primIndex, TriangleShapeEx^ triangle);
			void GetIndices(int faceIndex, unsigned int% i0, unsigned int% i1, unsigned int% i2);
			void GetVertex(unsigned int vertexIndex, [Out] Vector3% vertex);
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

			property int VertexCount
			{
				int get();
			}
		};
#endif

	internal:
		GImpactMeshShapePart(btGImpactMeshShapePart* native);

	public:
		GImpactMeshShapePart();
		GImpactMeshShapePart(StridingMeshInterface^ meshInterface, int part);

		void GetVertex(int vertexIndex, [Out] Vector3% vertex);

#ifndef DISABLE_BVH
		property TrimeshPrimitiveManager^ GImpactTrimeshPrimitiveManager
		{
			TrimeshPrimitiveManager^ get();
		}
#endif

		property int Part
		{
			int get();
		}

#ifndef DISABLE_BVH
		property PrimitiveManagerBase^ PrimitiveManager
		{
			virtual PrimitiveManagerBase^ get() override;
		}
#endif

		property int VertexCount
		{
			int get();
		}
	};

	public ref class GImpactMeshShape : GImpactShapeInterface
	{
		StridingMeshInterface^ _meshInterface;
		array<GImpactMeshShapePart^>^ _meshParts;

	internal:
		GImpactMeshShape(btGImpactMeshShape* native);

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

#ifndef DISABLE_BVH
		property PrimitiveManagerBase^ PrimitiveManager
		{
			virtual PrimitiveManagerBase^ get() override;
		}
#endif
	};
};
