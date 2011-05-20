#pragma once

namespace BulletSharp
{
	ref class Aabb;
	ref class AlignedIntArray;
	ref class PrimitiveManagerBase;
	ref class PrimitiveTriangle;
	ref class UShortArray;

	public ref class QuantizedBvhNode
	{
	internal:
		BT_QUANTIZED_BVH_NODE* _node;

	public:
		QuantizedBvhNode();
		QuantizedBvhNode(BT_QUANTIZED_BVH_NODE* node);
		QuantizedBvhNode(const BT_QUANTIZED_BVH_NODE* node);

		bool TestQuantizedBoxOverlap(array<unsigned short>^ quantizedMin, array<unsigned short>^ quantizedMax);

		property int DataIndex
		{
			int get();
			void set(int value);
		}

		property int EscapeIndex
		{
			int get();
			void set(int value);
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

	public ref class GImpactQuantizedBvh
	{
	private:
		btGImpactQuantizedBvh* _bvh;

	internal:
		GImpactQuantizedBvh(btGImpactQuantizedBvh* bvh);

	public:
		GImpactQuantizedBvh();
		GImpactQuantizedBvh(PrimitiveManagerBase^ primitiveManager);

		bool BoxQuery(Aabb^ box, [Out] AlignedIntArray^% collided_results);
		bool BoxQueryTrans(Aabb^ box, Matrix transform, [Out] AlignedIntArray^% collided_results);
		void BuildSet();
		static void FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs);
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, [Out] Aabb^% bound);
		int GetNodeData(int nodeIndex);
		QuantizedBvhNode^ GetNodePointer(int index);
		QuantizedBvhNode^ GetNodePointer();
		void GetNodeTriangle(int nodeIndex, [Out] PrimitiveTriangle^% triangle);
		int GetRightNode(int nodeIndex);
		bool IsLeafNode(int nodeIndex);
		bool RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] AlignedIntArray^% collided_results);
		void SetNodeBound(int nodeIndex, Aabb^ bound);
		void Update();

		//property float AverageTreeCollisionTime
		//{
		//	static float get();
		//}

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
			void set(PrimitiveManagerBase^ value);
		}
	};
};
