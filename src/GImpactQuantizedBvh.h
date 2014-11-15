#pragma once

namespace BulletSharp
{
	ref class Aabb;
	ref class AlignedIntArray;
	ref class PrimitiveManagerBase;
	ref class PrimitiveTriangle;
	ref class UShortArray;

	public ref class GImpactQuantizedBvhNode : IDisposable
	{
	internal:
		BT_QUANTIZED_BVH_NODE* _native;

		GImpactQuantizedBvhNode(BT_QUANTIZED_BVH_NODE* native);

	public:
		!GImpactQuantizedBvhNode();
	protected:
		~GImpactQuantizedBvhNode();

	public:
		GImpactQuantizedBvhNode();

		bool TestQuantizedBoxOverlap(array<unsigned short>^ quantizedMin, array<unsigned short>^ quantizedMax);

		property int DataIndex
		{
			int get();
			void set(int index);
		}

		property int EscapeIndex
		{
			int get();
			void set(int index);
		}

		property int EscapeIndexOrDataIndex
		{
			int get();
			void set(int value);
		}

		property bool IsLeafNode
		{
			bool get();
		}

		property UShortArray^ QuantizedAabbMin
		{
			UShortArray^ get();
		}

		property UShortArray^ QuantizedAabbMax
		{
			UShortArray^ get();
		}
	};

	public ref class GimGImpactQuantizedBvhNodeArray // : AlignedGImpactQuantizedBvhNodeArray
	{
	internal:
		GIM_QUANTIZED_BVH_NODE_ARRAY* _native;
		GimGImpactQuantizedBvhNodeArray(GIM_QUANTIZED_BVH_NODE_ARRAY* native);

	public:
		GimGImpactQuantizedBvhNodeArray();
	};

	public ref class QuantizedBvhTree : IDisposable
	{
	internal:
		btQuantizedBvhTree* _native;

		QuantizedBvhTree(btQuantizedBvhTree* native);

	public:
		!QuantizedBvhTree();
	protected:
		~QuantizedBvhTree();

	public:
		QuantizedBvhTree();

		//void BuildTree(GimBvhDataArray^ primitiveBoxes);
		void ClearNodes();
		//GImpactQuantizedBvhNode^ GetNodePointer(int index);
		//GImpactQuantizedBvhNode^ GetNodePointer();
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, Aabb^ bound);
		int GetNodeData(int nodeIndex);
		int GetRightNode(int nodeIndex);
		bool IsLeafNode(int nodeIndex);
		void QuantizePoint(UShortArray^ quantizedpoint, Vector3 point);
		void SetNodeBound(int nodeIndex, Aabb^ bound);
		bool TestQuantizedBoxOverlap(int nodeIndex, UShortArray^ quantizedMin,
			UShortArray^ quantizedMax);

		property int NodeCount
		{
			int get();
		}
	};

	public ref class GImpactQuantizedBvh : IDisposable
	{
	internal:
		btGImpactQuantizedBvh* _native;

		GImpactQuantizedBvh(btGImpactQuantizedBvh* native);

	private:
		PrimitiveManagerBase^ _primitiveManager;

	public:
		!GImpactQuantizedBvh();
	protected:
		~GImpactQuantizedBvh();

	public:
		GImpactQuantizedBvh();
		GImpactQuantizedBvh(PrimitiveManagerBase^ primitiveManager);

		bool BoxQuery(Aabb^ box, AlignedIntArray^ collidedResults);
		bool BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collidedResults);
		void BuildSet();
		static void FindCollision(GImpactQuantizedBvh^ boxset1, Matrix trans1, GImpactQuantizedBvh^ boxset2,
			Matrix trans2, PairSet^ collisionPairs);
		//GImpactQuantizedBvhNode^ GetNodePointer(int index);
		//GImpactQuantizedBvhNode^ GetNodePointer();
		int GetEscapeNodeIndex(int nodeindex);
		int GetLeftNode(int nodeindex);
		void GetNodeBound(int nodeindex, Aabb^ bound);
		int GetNodeData(int nodeindex);
		void GetNodeTriangle(int nodeindex, PrimitiveTriangle^ triangle);
		int GetRightNode(int nodeindex);
		bool IsLeafNode(int nodeindex);
		bool RayQuery(Vector3 rayDir, Vector3 rayOrigin, AlignedIntArray^ collidedResults);
		void SetNodeBound(int nodeindex, Aabb^ bound);
		void Update();

		property Aabb^ GlobalBox
		{
			Aabb^ get();
		}

		property bool HasHierarchy
		{
			bool get();
		}

		property bool IsTrimesh
		{
			bool get();
		}

		property int NodeCount
		{
			int get();
		}

		property PrimitiveManagerBase^ PrimitiveManager
		{
			PrimitiveManagerBase^ get();
			void set(PrimitiveManagerBase^ primitiveManager);
		}
	};
};
