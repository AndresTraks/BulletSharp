#pragma once

#include "CollisionShape.h"

UsingFrameworkNamespace

namespace BulletSharp
{
	public ref class CompoundShape : CollisionShape
	{
	public:
		CompoundShape();
		CompoundShape(bool enableDynamicAabbTree);

		void AddChildShape(Matrix localTransform, CollisionShape^ shape);

	internal:
		property btCompoundShape* UnmanagedPointer
		{
			btCompoundShape* get();
		}
	};
};
