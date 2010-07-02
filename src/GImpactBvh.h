#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactBvh.h>
#pragma managed(pop)

#include "IDisposable.h"

namespace BulletSharp
{
	ref class Aabb;
	ref class IntArray;
	ref class PrimitiveTriangle;

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
//		void GetPrimitiveTriangle(int prim_index, PrimitiveTriangle^ triangle);

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

		property PrimitiveManagerBase^ PrimitiveManager
		{
			PrimitiveManagerBase^ get();
			void set(PrimitiveManagerBase^ value);
		}
	};
};
