#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class TriangleCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btTriangleCallback* _callback;

	internal:
		TriangleCallback(btTriangleCallback* callback);

	public:
		!TriangleCallback();
	protected:
		~TriangleCallback();

	public:
		void ProcessTriangle(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btTriangleCallback* UnmanagedPointer
		{
			btTriangleCallback* get();
			void set(btTriangleCallback* value);
		}
	};

#ifndef DISABLE_INTERNAL
	public ref class InternalTriangleIndexCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btInternalTriangleIndexCallback* _callback;

	internal:
		InternalTriangleIndexCallback(btInternalTriangleIndexCallback* callback);

	public:
		!InternalTriangleIndexCallback();
	protected:
		~InternalTriangleIndexCallback();

	public:
		void InternalProcessTriangleIndex(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btInternalTriangleIndexCallback* UnmanagedPointer
		{
			btInternalTriangleIndexCallback* get();
			void set(btInternalTriangleIndexCallback* value);
		}
	};
#endif
};
