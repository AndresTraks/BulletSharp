#include "StdAfx.h"

#include "EmptyShape.h"

EmptyShape::EmptyShape(btEmptyShape* native)
	: ConcaveShape(native)
{
}

EmptyShape::EmptyShape()
	: ConcaveShape(new btEmptyShape())
{
}
