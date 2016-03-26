#pragma once

namespace BulletSharp
{
	ref class DataStream;
	ref class InternalTriangleIndexCallback;
	ref class Serializer;

	public ref class StridingMeshInterface abstract
	{
	internal:
		btStridingMeshInterface* _native;

		StridingMeshInterface(btStridingMeshInterface* native);
		static StridingMeshInterface^ GetManaged(btStridingMeshInterface* stridingMesh);

		~StridingMeshInterface();
		!StridingMeshInterface();

	public:
		void CalculateAabbBruteForce([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void GetLockedReadOnlyVertexIndexData([Out] DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type,
			[Out] int% vertexStride, [Out] DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType,
			int subpart);
		void GetLockedReadOnlyVertexIndexData([Out] DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type,
			[Out] int% vertexStride, [Out] DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType);

		void GetLockedVertexIndexData([Out] DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type,
			[Out] int% vertexStride, [Out] DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType,
			int subpart);
		void GetLockedVertexIndexData([Out] DataStream^% vertexData, [Out] int% numVerts, [Out] PhyScalarType% type,
			[Out] int% vertexStride, [Out] DataStream^% indexData, [Out] int% indexStride, [Out] int% numFaces, [Out] PhyScalarType% indicesType);
		void GetPremadeAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
#ifndef DISABLE_INTERNAL
		void InternalProcessAllTriangles(InternalTriangleIndexCallback^ callback,
			Vector3 aabbMin, Vector3 aabbMax);
#endif
		void PreallocateIndices(int numIndices);
		void PreallocateVertices(int numVerts);
#ifndef DISABLE_SERIALIZE
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
#endif
		void SetPremadeAabb(Vector3 aabbMin, Vector3 aabbMax);
		void UnlockReadOnlyVertexData(int subpart);
		void UnlockVertexData(int subpart);

		property bool HasPremadeAabb
		{
			bool get();
		}

		property int NumSubParts
		{
			int get();
		}

		property Vector3 Scaling
		{
			Vector3 get();
			void set(Vector3 scaling);
		}

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
};
