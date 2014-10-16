#pragma once

namespace BulletSharp
{
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class BulletMaterial
	{
	private:
		btScalar friction;
		btScalar restitution;
		int pad1;
		int pad2;

	internal:
		BulletMaterial(btMaterial* native);

	public:
		BulletMaterial(btScalar fric, btScalar rest);

		static property int SizeInBytes { int get() { return System::Runtime::InteropServices::Marshal::SizeOf(BulletMaterial::typeid); } }

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
