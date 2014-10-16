#pragma once

// btSparseSdf is only used in btSoftBody as btSparseSdf<3>,
// so that's what we define it as.

namespace BulletSharp
{
	ref class CollisionShape;

	public ref class SparseSdf
	{
	internal:
		btSparseSdf<3>* _native;
		SparseSdf(btSparseSdf<3>* native);

	public:
		void GarbageCollect(int lifetime);
		void GarbageCollect();
		void Initialize(int hashSize);
		void Initialize();
		int RemoveReferences(CollisionShape^ pcs);
		void Reset();
	};
};
