#pragma once

// Fully implemented as of 23 Mar 2010

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class BoxShape;

	public ref class BoxBoxDetector : DiscreteCollisionDetectorInterface
	{
	internal:
		BoxBoxDetector(btBoxBoxDetector* detector);
	public:
		BoxBoxDetector(BoxShape^ box1, BoxShape^ box2);

		property BoxShape^ Box1
		{
			BoxShape^ get();
			void set(BoxShape^ value);
		}

		property BoxShape^ Box2
		{
			BoxShape^ get();
			void set(BoxShape^ value);
		}

	internal:
		property btBoxBoxDetector* UnmanagedPointer
		{
			btBoxBoxDetector* get() new;
		}
	};
};
