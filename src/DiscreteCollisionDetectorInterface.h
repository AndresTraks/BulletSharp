#pragma once

namespace BulletSharp
{
	struct btStorageResultWrapper;

	interface class IDebugDraw;

	public ref class DiscreteCollisionDetectorInterface : ITrackingDisposable
	{
	public:
		ref class ClosestPointInput
		{
		internal:
			btDiscreteCollisionDetectorInterface::ClosestPointInput* _native;

		public:
			!ClosestPointInput();
		protected:
			~ClosestPointInput();

		public:
			ClosestPointInput();

			property btScalar MaximumDistanceSquared
			{
				btScalar get();
				void set(btScalar value);
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
		};

		ref class Result abstract : IDisposable
		{
		internal:
			btDiscreteCollisionDetectorInterface::Result* _native;
			Result(btDiscreteCollisionDetectorInterface::Result* result);

		public:
			!Result();
		protected:
			~Result();

		public:
			virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth) abstract;
			virtual void SetShapeIdentifiersA(int partId0, int index0) abstract;
			virtual void SetShapeIdentifiersB(int partId1, int index1) abstract;

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btDiscreteCollisionDetectorInterface* _native;
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
	};

	public ref class StorageResult abstract : DiscreteCollisionDetectorInterface::Result
	{
	internal:
		StorageResult(btStorageResultWrapper* result);

	public:
		StorageResult();

		virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth) new;

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
	};

	struct btStorageResultWrapper : public btStorageResult
	{
	private:
		gcroot<StorageResult^> _storageResult;

	public:
		btStorageResultWrapper(gcroot<StorageResult^> storageResult);

		virtual void setShapeIdentifiersA(int partId0, int index0);
		virtual void setShapeIdentifiersB(int partId1, int index1);
	};
};
