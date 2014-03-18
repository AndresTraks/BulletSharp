#pragma once

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	public ref class PointCollector : DiscreteCollisionDetectorInterface::Result
	{
	public:
		PointCollector();

		virtual void AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld, btScalar depth) override;
		virtual void SetShapeIdentifiersA(int partId0, int index0) override;
		virtual void SetShapeIdentifiersB(int partId1, int index1) override;

		property btScalar Distance
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool HasResult
		{
			bool get();
			void set(bool value);
		}

		property Vector3 NormalOnBInWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 PointInWorld
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};
};
