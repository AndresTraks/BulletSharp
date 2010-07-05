#include "StdAfx.h"

#include "GImpactQuantizedBvh.h"

GImpactQuantizedBvh::GImpactQuantizedBvh(btGImpactQuantizedBvh* bvh)
{
	_bvh = bvh;
}

GImpactQuantizedBvh::GImpactQuantizedBvh()
{
	_bvh = new btGImpactQuantizedBvh();
}
