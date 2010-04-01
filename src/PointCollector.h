#pragma once

// Fully implemented as of 02 Apr 2010

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	public ref class PointCollector : DiscreteCollisionDetectorInterface::Result
	{
	public:
		PointCollector();

		property btScalar Distance
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool HasResult
		{
			bool get();
			void set(bool value);
		}

		property Vector3 NormalOnBInWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 PointInWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

	internal:
		property btPointCollector* UnmanagedPointer
		{
			virtual btPointCollector* get() new;
		}
	};
};
