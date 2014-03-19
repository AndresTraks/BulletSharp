#pragma once

namespace BulletSharp
{
	ref class Aabb;
	ref class AlignedIntArray;
	ref class PrimitiveManagerBase;
	ref class PrimitiveTriangle;
	ref class UShortArray;

	public ref class GImpactQuantizedBvhNode
	{
	internal:
		BT_QUANTIZED_BVH_NODE* _native;
		GImpactQuantizedBvhNode(BT_QUANTIZED_BVH_NODE* native);

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

	public ref class QuantizedBvhTree
	{
	internal:
		btQuantizedBvhTree* _native;
		QuantizedBvhTree(btQuantizedBvhTree* native);

	public:
		QuantizedBvhTree();

		//void BuildTree(GimBvhDataArray^ primitive_boxes);
		void ClearNodes();
		//GImpactQuantizedBvhNode^ GetNodePointer(int index);
		//GImpactQuantizedBvhNode^ GetNodePointer();
		int GetEscapeNodeIndex(int NodeIndex);
		int GetLeftNode(int NodeIndex);
		void GetNodeBound(int NodeIndex, Aabb^ bound);
		int GetNodeData(int NodeIndex);
		int GetRightNode(int NodeIndex);
		bool IsLeafNode(int NodeIndex);
		void QuantizePoint(UShortArray^ quantizedpoint, Vector3 point);
		void SetNodeBound(int NodeIndex, Aabb^ bound);
		bool TestQuantizedBoxOverlap(int NodeIndex, UShortArray^ quantizedMin,
			UShortArray^ quantizedMax);

		property int NodeCount
		{
			int get();
		}
	};

	public ref class GImpactQuantizedBvh
	{
	internal:
		btGImpactQuantizedBvh* _native;
		GImpactQuantizedBvh(btGImpactQuantizedBvh* native);

	private:
		PrimitiveManagerBase^ _primitiveManagerBase;

	public:
		GImpactQuantizedBvh();
		GImpactQuantizedBvh(PrimitiveManagerBase^ primitive_manager);

		bool BoxQuery(Aabb^ box, AlignedIntArray^ collided_results);
		bool BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collided_results);
		void BuildSet();
		static void FindCollision(GImpactQuantizedBvh^ boxset1, Matrix trans1, GImpactQuantizedBvh^ boxset2,
			Matrix trans2, PairSet^ collision_pairs);
		//GImpactQuantizedBvhNode^ GetNodePointer(int index);
		//GImpactQuantizedBvhNode^ GetNodePointer();
		int GetEscapeNodeIndex(int nodeindex);
		int GetLeftNode(int nodeindex);
		void GetNodeBound(int nodeindex, Aabb^ bound);
		int GetNodeData(int nodeindex);
		void GetNodeTriangle(int nodeindex, PrimitiveTriangle^ triangle);
		int GetRightNode(int nodeindex);
		bool IsLeafNode(int nodeindex);
		bool RayQuery(Vector3 ray_dir, Vector3 ray_origin, AlignedIntArray^ collided_results);
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
			void set(PrimitiveManagerBase^ primitive_manager);
		}
	};
};
