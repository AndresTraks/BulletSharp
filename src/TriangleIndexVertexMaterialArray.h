#pragma once

// Fully implemented as of 23 Nov 2010

#include "BulletMaterial.h"
#include "TriangleIndexVertexArray.h"

namespace BulletSharp
{
	ref class DataStream;

	public ref class MaterialProperties
	{
	private:
		btMaterialProperties* _properties;

	public:
		MaterialProperties();

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

	internal:
		property btMaterialProperties* UnmanagedPointer
		{
			btMaterialProperties* get();
		}
	};

	public ref class TriangleIndexVertexMaterialArray : TriangleIndexVertexArray
	{
	internal:
		TriangleIndexVertexMaterialArray(btTriangleIndexVertexMaterialArray* triangleArray);

	public:
		TriangleIndexVertexMaterialArray();
		TriangleIndexVertexMaterialArray(int numTriangles, IntPtr triangleIndexBase,
			int triangleIndexStride, int numVertices, IntPtr vertexBase, int vertexStride,
			int numMaterials, IntPtr materialBase, int materialStride, IntPtr triangleMaterialsBase,
			int materialIndexStride);
		TriangleIndexVertexMaterialArray(array<int>^ indices, array<Vector3>^ vertices,
			array<BulletMaterial>^ materials, array<int>^ materialIndices);

		void AddMaterialProperties(MaterialProperties^ mat, PhyScalarType triangleType);

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

	internal:
		property btTriangleIndexVertexMaterialArray* UnmanagedPointer
		{
			btTriangleIndexVertexMaterialArray* get() new;
		}
	};
};
