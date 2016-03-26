#pragma once

namespace BulletSharp
{
	public ref class TriangleCallback abstract
	{
	internal:
		btTriangleCallback* _native;

		TriangleCallback(btTriangleCallback* native);

		~TriangleCallback();
		!TriangleCallback();

	public:
		//void ProcessTriangle(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};

#ifndef DISABLE_INTERNAL
	public ref class InternalTriangleIndexCallback abstract
	{
	internal:
		btInternalTriangleIndexCallback* _native;

		InternalTriangleIndexCallback(btInternalTriangleIndexCallback* native);

		~InternalTriangleIndexCallback();
		!InternalTriangleIndexCallback();

	public:
		//void InternalProcessTriangleIndex(Vector3 triangle, int partId, int triangleIndex);

		property bool IsDisposed
		{
			virtual bool get();
		}
	};
#endif
};
