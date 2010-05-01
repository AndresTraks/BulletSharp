#include "StdAfx.h"

#include "EmptyShape.h"

EmptyShape::EmptyShape(btEmptyShape* shape)
: ConcaveShape(shape)
{
}

EmptyShape::EmptyShape()
: ConcaveShape(new btEmptyShape())
{
}
