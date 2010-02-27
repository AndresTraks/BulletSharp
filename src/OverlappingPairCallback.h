#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class OverlappingPairCallback : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;
	
	private:
		btOverlappingPairCallback* _pairCallback;

	protected:
		OverlappingPairCallback(btOverlappingPairCallback* pairCallback);
	public:
		!OverlappingPairCallback();
	protected:
		~OverlappingPairCallback();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btOverlappingPairCallback* UnmanagedPointer
		{
			virtual btOverlappingPairCallback* get();
			void set(btOverlappingPairCallback* value);
		}
	};
};