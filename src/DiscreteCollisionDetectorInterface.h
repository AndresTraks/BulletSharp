#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class DiscreteCollisionDetectorInterface : BulletSharp::IDisposable
	{
	public:
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
