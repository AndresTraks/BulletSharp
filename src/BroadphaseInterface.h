#pragma once

#include "BroadphaseProxy.h"
#include "IDisposable.h"
#include "IDispatcher.h"
#include "OverlappingPairCache.h"

namespace BulletSharp
{
	public ref class BroadphaseRayCallback
	{
		protected:
			btBroadphaseRayCallback* _rayCallback;

		internal:
			property btBroadphaseRayCallback* UnmanagedPointer
			{
				virtual btBroadphaseRayCallback* get();
				void set(btBroadphaseRayCallback* value);
			}
	};

	public ref class BroadphaseInterface abstract : BulletSharp::IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btBroadphaseInterface* _broadphase;
		protected:
			OverlappingPairCache^ _pairCache;

		protected:
			BroadphaseInterface(btBroadphaseInterface* broadphase);
		public:
			!BroadphaseInterface();
		protected:
			~BroadphaseInterface();
		public:
			property bool IsDisposed
			{
				virtual bool get();
			}

		public:
			void CalculateOverlappingPairs(IDispatcher^ dispatcher);
			BroadphaseProxy^ CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
				int shapeType, IntPtr userPtr, short int collisionFilterGroup,
				short int collisionFilterMask, IDispatcher^ dispatcher, IntPtr multiSapProxy);
			void DestroyProxy(BroadphaseProxy^ proxy, IDispatcher^ dispatcher);
			void GetAabb(BroadphaseProxy^ proxy, [Out] Vector3% aabbMin, [Out] Vector3% AabbMax);
			void GetBroadphaseAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
			void PrintStats();
			void RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback);
			void ResetPool(IDispatcher^ dispatcher);
			void SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, IDispatcher^ dispatcher);

			property BulletSharp::OverlappingPairCache^ OverlappingPairCache
			{
				BulletSharp::OverlappingPairCache^ get();
			}

		internal:
			property btBroadphaseInterface* UnmanagedPointer
			{
				virtual btBroadphaseInterface* get();
				void set(btBroadphaseInterface* value);
			}
	};
};
