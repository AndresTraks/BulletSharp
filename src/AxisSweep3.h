#pragma once

#include "BroadphaseInterface.h"

namespace BulletSharp
{
	ref class OverlappingPairCache;
	ref class OverlappingPairCallback;

	public ref class AxisSweep3 : BroadphaseInterface
	{
	private:
		OverlappingPairCallback^ _overlappingPairUserCallback;

	public:
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned short maxHandles);
		AxisSweep3(Vector3 worldAabbMin, Vector3 worldAabbMax);

		unsigned short AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy);
		unsigned short AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy);
		virtual BroadphaseProxy^ CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
			BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy) override;
		//Handle^ GetHandle(unsigned short index);
		//void ProcessAllOverlappingPairs(OverlapCallback^ callback);
		void Quantize([Out] unsigned short% out, Vector3 point, int isMax);
		void RemoveHandle(unsigned short handle, Dispatcher^ dispatcher);
		bool TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		void UnQuantize(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax);
		void UpdateHandle(unsigned short handle, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher);

		property unsigned short NumHandles
		{
			unsigned short get();
		}

		property OverlappingPairCallback^ OverlappingPairUserCallback
		{
			OverlappingPairCallback^ get();
			void set(OverlappingPairCallback^ pairCallback);
		}
	};

	public ref class AxisSweep3_32Bit : BroadphaseInterface
	{
	private:
		OverlappingPairCallback^ _overlappingPairUserCallback;

	public:
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache, bool disableRaycastAccelerator);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles,
			BulletSharp::OverlappingPairCache^ pairCache);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax, unsigned int maxHandles);
		AxisSweep3_32Bit(Vector3 worldAabbMin, Vector3 worldAabbMax);

		unsigned int AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy);
		unsigned int AddHandle(Vector3 aabbMin, Vector3 aabbMax, IntPtr pOwner, CollisionFilterGroups collisionFilterGroup,
			CollisionFilterGroups collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy);
		virtual BroadphaseProxy^ CreateProxy(Vector3% aabbMin, Vector3% aabbMax,
			BroadphaseNativeType shapeType, IntPtr userPtr, short collisionFilterGroup,
			short collisionFilterMask, Dispatcher^ dispatcher, IntPtr multiSapProxy) override;
		//Handle^ GetHandle(unsigned short index);
		//void ProcessAllOverlappingPairs(OverlapCallback^ callback);
		void Quantize([Out] unsigned int% out, Vector3 point, int isMax);
		void RemoveHandle(unsigned int handle, Dispatcher^ dispatcher);
		bool TestAabbOverlap(BroadphaseProxy^ proxy0, BroadphaseProxy^ proxy1);
		void UnQuantize(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax);
		void UpdateHandle(unsigned int handle, Vector3 aabbMin, Vector3 aabbMax, Dispatcher^ dispatcher);

		property unsigned int NumHandles
		{
			unsigned int get();
		}

		property OverlappingPairCallback^ OverlappingPairUserCallback
		{
			OverlappingPairCallback^ get();
			void set(OverlappingPairCallback^ pairCallback);
		}
	};
};
