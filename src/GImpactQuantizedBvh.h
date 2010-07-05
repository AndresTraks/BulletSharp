#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactQuantizedBvh.h>
#pragma managed(pop)

namespace BulletSharp
{
	public ref class GImpactQuantizedBvh
	{
	private:
		btGImpactQuantizedBvh* _bvh;

	internal:
		GImpactQuantizedBvh(btGImpactQuantizedBvh* bvh);

	public:
		GImpactQuantizedBvh();
	};
};
