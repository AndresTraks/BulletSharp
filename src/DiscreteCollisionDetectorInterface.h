#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class DebugDraw;
	ref class StackAlloc;

	public ref class DiscreteCollisionDetectorInterface : BulletSharp::IDisposable
	{
	public:
		ref class ClosestPointInput
		{
		private:
			btDiscreteCollisionDetectorInterface::ClosestPointInput* _input;
		public:
			ClosestPointInput();

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

		private:
			btDiscreteCollisionDetectorInterface::Result* _result;

		internal:
			Result(btDiscreteCollisionDetectorInterface::Result* result);
		public:
			!Result();
		protected:
			~Result();
		public:
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

		ref class StorageResult : Result
		{
		internal:
			StorageResult(btStorageResult* result);
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
		void GetClosestPoints(ClosestPointInput^ input, Result^ output, DebugDraw^ debugDraw);
		//void GetClosestPoints(ClosestPointInput^ input, [Out] Result^ %output, DebugDraw^ debugDraw);
		//void GetClosestPoints(ClosestPointInput^ input, Result^ output, DebugDraw^ debugDraw, bool swapResults);

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
};
