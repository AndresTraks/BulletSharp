#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class StackAlloc;
	interface class IDebugDraw;

	public ref class DiscreteCollisionDetectorInterface : BulletSharp::IDisposable
	{
	public:
		ref class ClosestPointInput
		{
		private:
			btDiscreteCollisionDetectorInterface::ClosestPointInput* _input;

		public:
			ClosestPointInput();

			property btScalar MaximumDistanceSquared
			{
				btScalar get();
				void set(btScalar value);
			}

			property BulletSharp::StackAlloc^ StackAlloc
			{
				BulletSharp::StackAlloc^ get();
				void set(BulletSharp::StackAlloc^ value);
			}

			property Matrix TransformA
			{
				Matrix get();
				void set(Matrix value);
			}

			property Matrix TransformB
			{
				Matrix get();
				void set(Matrix value);
			}

		internal:
			property btDiscreteCollisionDetectorInterface::ClosestPointInput* UnmanagedPointer
			{
				btDiscreteCollisionDetectorInterface::ClosestPointInput* get();
				void set(btDiscreteCollisionDetectorInterface::ClosestPointInput* value);
			}
		};

		ref class Result : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		internal:
			btDiscreteCollisionDetectorInterface::Result* _unmanaged;
			Result(btDiscreteCollisionDetectorInterface::Result* result);

		public:
			!Result();
		protected:
			~Result();

		public:
			virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth);
			virtual void SetShapeIdentifiersA(int partId0, int index0);
			virtual void SetShapeIdentifiersB(int partId1, int index1);

			property bool IsDisposed
			{
				virtual bool get();
			}

		internal:
			property btDiscreteCollisionDetectorInterface::Result* UnmanagedPointer
			{
				btDiscreteCollisionDetectorInterface::Result* get();
				void set(btDiscreteCollisionDetectorInterface::Result* value);
			}
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btDiscreteCollisionDetectorInterface* _detectorInterface;

	internal:
		DiscreteCollisionDetectorInterface(btDiscreteCollisionDetectorInterface* dispatcher);
	public:
		!DiscreteCollisionDetectorInterface();
	protected:
		~DiscreteCollisionDetectorInterface();
	public:
#ifndef DISABLE_DEBUGDRAW
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw);
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw, bool swapResults);
#else
		void GetClosestPoints(ClosestPointInput^ input, Result^ output);
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, bool swapResults);
#endif

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btDiscreteCollisionDetectorInterface* UnmanagedPointer
		{
			btDiscreteCollisionDetectorInterface* get();
			void set(btDiscreteCollisionDetectorInterface* value);
		}
	};

	class btStorageResultWrapper;

	//public
	ref class StorageResult : DiscreteCollisionDetectorInterface::Result
	{
	internal:
		StorageResult(btStorageResultWrapper* result);

	public:
		StorageResult();

		//virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth);
		virtual void SetShapeIdentifiersA(int partId0, int index0) new;
		virtual void SetShapeIdentifiersB(int partId1, int index1) new;

		property Vector3 ClosestPointInB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Distance
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 NormalOnSurfaceB
		{
			Vector3 get();
			void set(Vector3 value);
		}

	internal:
		property btStorageResultWrapper* UnmanagedPointer
		{
			btStorageResultWrapper* get() new;
		}
	};

	class btStorageResultWrapper : public btStorageResult
	{
	private:
		auto_gcroot<StorageResult^> _storageResult;

	public:
//		btStorageResultWrapper(StorageResult^ storageResult);

		virtual void setShapeIdentifiersA(int partId0, int index0);
		virtual void setShapeIdentifiersB(int partId1, int index1);
	};
};
