#pragma once

#include "BroadphaseInterface.h"
#include "BroadphaseProxy.h"
#include "Enums.h"

namespace BulletSharp
{
	ref class BroadphaseProxy;
	ref class Dispatcher;
	ref class Dbvt;
	ref class OverlappingPairCache;

	public ref class DbvtNode
	{
	private:
		btDbvtNode* _node;
	internal:
		DbvtNode(btDbvtNode* node);

	internal:
		property btDbvtNode* UnmanagedPointer
		{
			virtual btDbvtNode* get();
			void set(btDbvtNode* value);
		}
	};

	public ref class DbvtProxy : BroadphaseProxy
	{
	internal:
		DbvtProxy(btDbvtProxy* proxy);
	public:
		DbvtProxy(Vector3 aabbMin, Vector3 aabbMax, IntPtr userPtr,
			CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask);

		property DbvtNode^ Leaf
		{
			DbvtNode^ get();
			void set(DbvtNode^ value);
		}

		property btDbvtProxy* UnmanagedPointer
		{
			btDbvtProxy* get() new;
		}
	};

	public ref class DbvtBroadphase : BroadphaseInterface
	{
	public:
		static int DynamicSet = btDbvtBroadphase::DYNAMIC_SET;
		static int FixedSet = btDbvtBroadphase::FIXED_SET;
		static int StageCount = btDbvtBroadphase::STAGECOUNT;

	public:
		DbvtBroadphase(BulletSharp::OverlappingPairCache^ pairCache);
		DbvtBroadphase();

		static void Benchmark(BroadphaseInterface^ broadphase);

		void Collide(Dispatcher^ dispatcher);
		void Optimize();
		void PerformDeferredRemoval(Dispatcher^ dispatcher);
		void SetAabbForceUpdate(BroadphaseProxy^ absproxy,
			Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher);

		property array<Dbvt^>^ Sets
		{
			array<Dbvt^>^ get();
			void set(array<Dbvt^>^ value);
		}

		property array<DbvtProxy^>^ StageRoots
		{
			array<DbvtProxy^>^ get();
			void set(array<DbvtProxy^>^ value);
		}

		property btScalar VelocityPrediction
		{
			btScalar get();
			void set(btScalar prediction);
		}

	internal:
		property btDbvtBroadphase* UnmanagedPointer
		{
			btDbvtBroadphase* get() new;
		}
	};
};