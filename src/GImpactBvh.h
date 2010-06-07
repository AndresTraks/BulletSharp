#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactBvh.h>
#pragma managed(pop)

namespace BulletSharp
{
	ref class Aabb;
	ref class IntArray;

	public ref class GImpactBvh
	{
	private:
		btGImpactBvh* _bvh;

	internal:
		GImpactBvh(btGImpactBvh* bvh);

	public:
		GImpactBvh();
		//GImpactBvh(PrimitiveManagerBase^ primitive_manager);

		bool BoxQuery(Aabb^ box, [Out] IntArray^% collided_results);
		bool BoxQuery(Aabb^ box, Matrix transform, [Out] IntArray^% collided_results);
		void BuildSet();
		//static void FindCollision(GImpactBvh^ boxset1, Matrix trans1, GImpactBvh^ boxset2, Matrix trans2, [Out] PairSet^% collision_pairs);
		//GimBvhTreeNode^ GetNodePointer(int index);
		//GimBvhTreeNode^ GetNodePointer();
		int GetEscapeNodeIndex(int nodeIndex);
		int GetLeftNode(int nodeIndex);
		void GetNodeBound(int nodeIndex, [Out] Aabb^% bound);
		int GetNodeData(int nodeIndex);
		//void GetNodeTriangle(int nodeindex, [Out] PrimitiveTriangle^% triangle);
		int GetRightNode(int nodeIndex);
		bool IsLeafNode(int nodeIndex);
		bool RayQuery(Vector3 ray_dir, Vector3 ray_origin, [Out] IntArray^% collided_results);
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

		//property PrimitiveManager^ PrimitiveManager
		//{
		//	PrimitiveManager^ get();
		//	void set(PrimitiveManager^ value);
		//}
	};
};
