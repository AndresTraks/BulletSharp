#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	public ref class SoftBodyWorldInfo
	{
	private:
		btSoftBodyWorldInfo* _info;
	internal:
		property btSoftBodyWorldInfo* UnmanagedPointer
		{
			btSoftBodyWorldInfo* get();
			void set(btSoftBodyWorldInfo* value);
		};
	};

	public ref class SoftBody : CollisionObject
	{
	internal:
		SoftBody(btSoftBody* body);
	public:
		SoftBody(SoftBodyWorldInfo^ worldInfo,
			int node_count, Vector3 x, btScalar m);
	};
};
