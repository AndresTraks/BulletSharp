#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class TriangleCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btTriangleCallback* _native;
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
	};

#ifndef DISABLE_INTERNAL
	public ref class InternalTriangleIndexCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btInternalTriangleIndexCallback* _native;

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
	};
#endif
};
