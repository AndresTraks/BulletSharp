#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btBoxCollision.h>
#pragma managed(pop)

namespace BulletSharp
{
	public ref class Aabb
	{
	private:
		btAABB* _aabb;

	internal:
		Aabb(btAABB* aabb);

	internal:
		property btAABB* UnmanagedPointer
		{
			btAABB* get();
		}
	};
};
