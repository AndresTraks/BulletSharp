#pragma once

namespace BulletSharp
{
	public ref class TriangleCallback abstract : IDisposable
	{
	internal:
		btTriangleCallback* _native;
		TriangleCallback(btTriangleCallback* native);

	public:
		!TriangleCallback();
	protected:
		~TriangleCallback();

	public:
		//void ProcessTriangle(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

#ifndef DISABLE_INTERNAL
	public ref class InternalTriangleIndexCallback abstract : IDisposable
	{
	internal:
		btInternalTriangleIndexCallback* _native;
		InternalTriangleIndexCallback(btInternalTriangleIndexCallback* native);

	public:
		!InternalTriangleIndexCallback();
	protected:
		~InternalTriangleIndexCallback();

	public:
		//void InternalProcessTriangleIndex(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
#endif
};
