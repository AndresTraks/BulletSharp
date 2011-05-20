#pragma once

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
