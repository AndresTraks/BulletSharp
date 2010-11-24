#pragma once

namespace BulletSharp
{
	public ref class Aabb
	{
	private:
		btAABB* _aabb;

	internal:
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

	internal:
		property btAABB* UnmanagedPointer
		{
			btAABB* get();
		}
	};
};
