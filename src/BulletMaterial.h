#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btMaterial.h>
#pragma managed(pop)

namespace BulletSharp
{
	public ref class BulletMaterial
	{
	private:
		btMaterial* _material;

	internal:
		BulletMaterial(btMaterial* material);

	public:
		BulletMaterial();
		BulletMaterial(btScalar fric, btScalar rest);

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar value);
		}
		
		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar value);
		}
	};
};
