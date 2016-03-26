#pragma once

#include "BulletMaterial.h"
#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	ref class DataStream;

	public ref class MaterialProperties
	{
	internal:
		btMaterialProperties* _native;

	private:
		bool _ownsData;

		~MaterialProperties();
		!MaterialProperties();

	public:
		MaterialProperties();

		void Allocate(int numMaterials, int numTriangles, int materialStride, int materialIndexStride,
			PhyScalarType materialType, PhyScalarType triangleType);
		void Free();

		property IntPtr MaterialBase
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int MaterialStride
		{
			int get();
			void set(int value);
		}

		property PhyScalarType MaterialType
		{
			PhyScalarType get();
			void set(PhyScalarType value);
		}

		property int NumMaterials
		{
			int get();
			void set(int value);
		}

		property int NumTriangles
		{
			int get();
			void set(int value);
		}

		property IntPtr TriangleMaterialsBase
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property int TriangleMaterialStride
		{
			int get();
			void set(int value);
		}

		property PhyScalarType TriangleType
		{
			PhyScalarType get();
			void set(PhyScalarType value);
		}
	};

	public ref class TriangleIndexVertexMaterialArray : TriangleIndexVertexArray
	{
	private:
		MaterialProperties^ _initialMaterialProperties;
		List<MaterialProperties^>^ _materialProperties;
		IndexedMesh^ _initialMesh;

	internal:
		TriangleIndexVertexMaterialArray(btTriangleIndexVertexMaterialArray* native);

		!TriangleIndexVertexMaterialArray();
		~TriangleIndexVertexMaterialArray();

	public:
		TriangleIndexVertexMaterialArray();
		TriangleIndexVertexMaterialArray(int numTriangles, IntPtr triangleIndexBase,
			int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride,
			int numMaterials, IntPtr materialBase, int materialStride, IntPtr triangleMaterialsBase,
			int materialIndexStride);
		TriangleIndexVertexMaterialArray(ICollection<int>^ indices, ICollection<Vector3>^ vertices,
			ICollection<BulletMaterial>^ materials, ICollection<int>^ materialIndices);

		void AddMaterialProperties(MaterialProperties^ mat, PhyScalarType triangleType);
		void AddMaterialProperties(MaterialProperties^ mat);
		void GetLockedMaterialData([Out] DataStream^% materialData, [Out] int% numMaterials,
			[Out] PhyScalarType% materialType, [Out] int% materialStride,
			[Out] DataStream^% triangleMaterialData, [Out] int% numTriangles,
			[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType,
			int subpart);
		void GetLockedMaterialData([Out] DataStream^% materialData, [Out] int% numMaterials,
			[Out] PhyScalarType% materialType, [Out] int% materialStride,
			[Out] DataStream^% triangleMaterialData, [Out] int% numTriangles,
			[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType);

		void GetLockedReadOnlyMaterialData([Out] DataStream^% materialData, [Out] int% numMaterials,
			[Out] PhyScalarType% materialType, [Out] int% materialStride,
			[Out] DataStream^% triangleMaterialData, [Out] int% numTriangles,
			[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType,
			int subpart);
		void GetLockedReadOnlyMaterialData([Out] DataStream^% materialData, [Out] int% numMaterials,
			[Out] PhyScalarType% materialType, [Out] int% materialStride,
			[Out] DataStream^% triangleMaterialData, [Out] int% numTriangles,
			[Out] int% triangleMaterialStride, [Out] PhyScalarType% triangleType);
	};
};
