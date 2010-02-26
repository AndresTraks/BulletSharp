#pragma once

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h>
#pragma managed(pop)

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class ConvexPenetrationDepthSolver : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btConvexPenetrationDepthSolver* _depthSolver;

	protected:
		ConvexPenetrationDepthSolver(btConvexPenetrationDepthSolver* depthSolver);
	public:
		!ConvexPenetrationDepthSolver();
	protected:
		~ConvexPenetrationDepthSolver();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	public:

	internal:
		property btConvexPenetrationDepthSolver* UnmanagedPointer
		{
			virtual btConvexPenetrationDepthSolver* get();
			void set(btConvexPenetrationDepthSolver* value);
		}
	};
};
