#pragma once

namespace BulletSharp
{
	public ref class Aabb
	{
	internal:
		btAABB* _native;

		Aabb(btAABB* aabb);

	public:
		property Vector3 Max
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 Min
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};
};
