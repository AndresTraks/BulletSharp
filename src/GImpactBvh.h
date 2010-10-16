#pragma once

// Fully implemented as of 06 Jul 2010

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactBvh.h>
#pragma managed(pop)

#include "IDisposable.h"

namespace BulletSharp
{
	ref class Aabb;
	ref class AlignedIntArray;
	ref class PrimitiveTriangle;

	public ref class PairSet // : GimPairArray
	{
	private:
		btPairSet* _pairSet;

	public:
		PairSet();
		PairSet(btPairSet* pairSet);

		void PushPair(int index1, int index2);
		void PushPairInv(int index1, int index2);
	};

	public ref class GimBvhTreeNode
	{
	internal:
		GIM_BVH_TREE_NODE* _node;

	public:
		GimBvhTreeNode();
		GimBvhTreeNode(GIM_BVH_TREE_NODE* node);
		GimBvhTreeNode(const GIM_BVH_TREE_NODE* node);

		property Aabb^ Bound
		{
			Aabb^ get();
			void set(Aabb^ value);
		}

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

		property bool IsLeafNode
		{
			bool get();
		}
	};

	public ref class PrimitiveManagerBase : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btPrimitiveManagerBase* _primitiveManager;

	internal:
		PrimitiveManagerBase(btPrimitiveManagerBase* primitiveManager);

	public:
		!PrimitiveManagerBase();
	protected:
		~PrimitiveManagerBase();

	public:
		void GetPrimitiveBox(int prim_index, [Out] Aabb^% primbox);
		void GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle);

		property bool IsTriMesh
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

	internal:
		property btPrimitiveManagerBase* UnmanagedPointer
		{
			virtual btPrimitiveManagerBase* get();
			void set(btPrimitiveManagerBase* value);
		}
	};

	public ref class GImpactBvh
	{
	private:
		btGImpactBvh* _bvh;

	internal:
		GImpactBvh(btGImpactBvh* bvh);

	public:
		GImpactBvh();
		GImpactBvh(PrimitiveManagerBase^ primitive_manager);

		bool BoxQuery(Aabb^ box, [Out] AlignedIntArray^% collided_results);
		bool BoxQueryTrans(Aabb^ box, Matrix transform, [Out] AlignedIntArray^% collided_results);
		void BuildSet();
		static void FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs);
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, [Out] Aabb^% bound);
		int GetNodeData(int nodeIndex);
		GimBvhTreeNode^ GetNodePointer(int index);
		GimBvhTreeNode^ GetNodePointer();
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

	internal:
		property btGImpactBvh* UnmanagedPointer
		{
			virtual btGImpactBvh* get();
			void set(btGImpactBvh* value);
		}
	};
};
