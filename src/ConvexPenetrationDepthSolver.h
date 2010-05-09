#pragma once

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

	internal:
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
