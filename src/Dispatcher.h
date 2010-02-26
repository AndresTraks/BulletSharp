#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class Dispatcher : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btDispatcher* _dispatcher;

	internal:
		Dispatcher(btDispatcher* dispatcher);
	public:
		!Dispatcher();
	protected:
		~Dispatcher();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	public:
		property btDispatcher* UnmanagedPointer
		{
			btDispatcher* get();
			void set(btDispatcher* value);
		}
	};
};
