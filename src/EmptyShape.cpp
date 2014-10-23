#include "StdAfx.h"

#include "EmptyShape.h"

EmptyShape::EmptyShape()
	: ConcaveShape(new btEmptyShape())
{
}
