#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btMaterial.h>
#pragma managed(pop)

namespace BulletSharp
{
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class BulletMaterial
	{
	public:
		btScalar Friction;
		btScalar Restitution;
	private:
		int pad1;
		int pad2;

	public:
		BulletMaterial(btMaterial* material);
		BulletMaterial(btScalar fric, btScalar rest);

		static property int SizeInBytes { int get() { return System::Runtime::InteropServices::Marshal::SizeOf(BulletMaterial::typeid); } }
	};
};
