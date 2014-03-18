#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class Aabb;
	ref class AlignedIntArray;
	ref class PrimitiveTriangle;
/*
	public ref class GimPair
	{
	internal:
		GIM_PAIR* _native;
		GimPair(GIM_PAIR* native);

	public:
		GimPair();
		GimPair(GimPair^ p);
		GimPair(int index1, int index2);

		property int Index1
		{
			int get();
			void set(int value);
		}

		property int Index2
		{
			int get();
			void set(int value);
		}
	};
*/
	public ref class PairSet // : GimPairArray
	{
	internal:
		btPairSet* _native;
		PairSet(btPairSet* native);

	public:
		PairSet();

		void PushPair(int index1, int index2);
		void PushPairInv(int index1, int index2);
	};
/*
	public ref class GimBvhData
	{
	internal:
		GIM_BVH_DATA* _native;
		GimBvhData(GIM_BVH_DATA* native);

	public:
		GimBvhData();

		property Aabb^ Bound
		{
			Aabb^ get();
			void set(Aabb^ value);
		}

		property int Data
		{
			int get();
			void set(int value);
		}
	};
*/
	public ref class GimBvhTreeNode
	{
	internal:
		GIM_BVH_TREE_NODE* _native;
		GimBvhTreeNode(GIM_BVH_TREE_NODE* native);

	public:
		GimBvhTreeNode();

		property Aabb^ Bound
		{
			Aabb^ get();
			void set(Aabb^ value);
		}

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

		property bool IsLeafNode
		{
			bool get();
		}
	};
/*
	public ref class GimBvhDataArray // : AlignedGimBvhDataArray
	{
	internal:
		GIM_BVH_DATA_ARRAY* _native;
		GimBvhDataArray(GIM_BVH_DATA_ARRAY* native);

	public:
		GimBvhDataArray();
	};

	public ref class GimBvhTreeNodeArray // : AlignedGimBvhTreeNodeArray
	{
	internal:
		GIM_BVH_TREE_NODE_ARRAY* _native;
		GimBvhTreeNodeArray(GIM_BVH_TREE_NODE_ARRAY* native);

	public:
		GimBvhTreeNodeArray();
	};
*/
	public ref class BvhTree
	{
	internal:
		btBvhTree* _native;
		BvhTree(btBvhTree* native);

	public:
		BvhTree();

		//void BuildTree(GimBvhDataArray^ primitive_boxes);
		void ClearNodes();
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, Aabb^ bound);
		int GetNodeData(int nodeIndex);
		//GimBvhTreeNode^ GetNodePointer(int index);
		//GimBvhTreeNode^ GetNodePointer();
		int GetRightNode(int nodeIndex);
		bool IsLeafNode(int nodeIndex);
		void SetNodeBound(int nodeIndex, Aabb^ bound);

		property int NodeCount
		{
			int get();
		}
	};

	public ref class PrimitiveManagerBase abstract : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btPrimitiveManagerBase* _native;
		PrimitiveManagerBase(btPrimitiveManagerBase* native);

	public:
		!PrimitiveManagerBase();
	protected:
		~PrimitiveManagerBase();

	public:
		void GetPrimitiveBox(int prim_index, Aabb^ primbox);
		void GetPrimitiveTriangle(int prim_index, PrimitiveTriangle^ triangle);

		property bool IsTrimesh
		{
			bool get();
		}

		property int PrimitiveCount
		{
			int get();
		}

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class GImpactBvh
	{
	internal:
		btGImpactBvh* _native;
		GImpactBvh(btGImpactBvh* native);

	private:
		PrimitiveManagerBase^ _primitiveManagerBase;

	public:
		GImpactBvh();
		GImpactBvh(PrimitiveManagerBase^ primitive_manager);

		bool BoxQuery(Aabb^ box, AlignedIntArray^ collided_results);
		bool BoxQueryTrans(Aabb^ box, Matrix transform, AlignedIntArray^ collided_results);
		void BuildSet();
		static void FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2,
			Matrix trans2, PairSet^ collision_pairs);
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, Aabb^ bound);
		int GetNodeData(int nodeIndex);
		//GimBvhTreeNode^ GetNodePointer(int index);
		//GimBvhTreeNode^ GetNodePointer();
		void GetNodeTriangle(int nodeIndex, PrimitiveTriangle^ triangle);
		int GetRightNode(int nodeIndex);
		bool IsLeafNode(int nodeIndex);
		bool RayQuery(Vector3 ray_dir, Vector3 ray_origin, AlignedIntArray^ collided_results);
		void SetNodeBound(int nodeIndex, Aabb^ bound);
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
