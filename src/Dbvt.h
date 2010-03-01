#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class Dbvt : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;
	
	private:
		btDbvt* _dbvt;

	public:
		Dbvt();

	internal:
		Dbvt(btDbvt* dbvt);
	public:
		!Dbvt();
	protected:
		~Dbvt();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btDbvt* UnmanagedPointer
		{
			virtual btDbvt* get();
			void set(btDbvt* value);
		}
	};
};
