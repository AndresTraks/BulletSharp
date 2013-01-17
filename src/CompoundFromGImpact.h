#pragma once

namespace BulletSharp
{
	ref class CompoundShape;
	ref class GImpactMeshShape;

	public ref class CompoundFromGImpact sealed
	{
	private:
		CompoundFromGImpact() {}

	public:
		static CompoundShape^ Create(GImpactMeshShape^ gImpactMesh, btScalar depth);
	};
};
