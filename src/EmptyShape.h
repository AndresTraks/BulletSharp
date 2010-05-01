#pragma once

// Fully implemented as of 03 Apr 2010

#include "ConcaveShape.h"

namespace BulletSharp
{
	public ref class EmptyShape : ConcaveShape
	{
	internal:
		EmptyShape(btEmptyShape* shape);
	public:
		EmptyShape();
	};
};
