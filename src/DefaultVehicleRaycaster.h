#pragma once

#include "VehicleRaycaster.h"

namespace BulletSharp
{
	ref class DynamicsWorld;

	public ref class DefaultVehicleRaycaster : VehicleRaycaster
	{
	public:
		DefaultVehicleRaycaster(DynamicsWorld^ world);
	};
};
