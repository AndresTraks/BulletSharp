#pragma once

// btSparseSdf is only used in btSoftBody as btSparseSdf<3>,
// so that's what we define it as.

namespace BulletSharp
{
	public ref class SparseSdf
	{
	internal:
		btSparseSdf<3>* _sdf;
		SparseSdf(btSparseSdf<3>* sdf);

	public:
		void GarbageCollect(int lifetime);
		void GarbageCollect();
		void Initialize(int hashSize);
		void Initialize();
		void Reset();

	internal:
		property btSparseSdf<3>* UnmanagedPointer
		{
			btSparseSdf<3>* get();
			void set(btSparseSdf<3>* value);
		};
	};
};
