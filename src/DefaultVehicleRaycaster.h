#pragma once

#include "DynamicsWorld.h"
#include "VehicleRaycaster.h"

namespace BulletSharp
{
	public ref class DefaultVehicleRaycaster : BulletSharp::VehicleRaycaster
	{
		public:
			DefaultVehicleRaycaster(DynamicsWorld^ world);
	};
};
