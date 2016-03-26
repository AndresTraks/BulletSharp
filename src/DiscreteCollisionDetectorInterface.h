#pragma once

namespace BulletSharp
{
	struct btStorageResultWrapper;

	interface class IDebugDraw;

	public ref class DiscreteCollisionDetectorInterface abstract
	{
	public:
		ref class ClosestPointInput
		{
		internal:
			btDiscreteCollisionDetectorInterface::ClosestPointInput* _native;

			~ClosestPointInput();
			!ClosestPointInput();

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

		ref class Result abstract
		{
		internal:
			btDiscreteCollisionDetectorInterface::Result* _native;

			Result(btDiscreteCollisionDetectorInterface::Result* native);

			~Result();
			!Result();

		public:
			virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth) abstract;
			virtual void SetShapeIdentifiersA(int partId0, int index0) abstract;
			virtual void SetShapeIdentifiersB(int partId1, int index1) abstract;

			property bool IsDisposed
			{
				virtual bool get();
			}
		};


	internal:
		btDiscreteCollisionDetectorInterface* _native;

		DiscreteCollisionDetectorInterface(btDiscreteCollisionDetectorInterface* native);

		~DiscreteCollisionDetectorInterface();
		!DiscreteCollisionDetectorInterface();

	public:
#ifndef DISABLE_DEBUGDRAW
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw,
			bool swapResults);
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, IDebugDraw^ debugDraw);
#else
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, bool swapResults);
		void GetClosestPoints(ClosestPointInput^ input, Result^ output);
#endif

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

	public ref class StorageResult abstract : DiscreteCollisionDetectorInterface::Result
	{
	internal:
		StorageResult(btStorageResultWrapper* native);

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
