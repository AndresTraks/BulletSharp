#include "StdAfx.h"

#ifndef DISABLE_VEHICLE

#include "DefaultVehicleRaycaster.h"
#include "DynamicsWorld.h"

DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
: VehicleRaycaster(new btDefaultVehicleRaycaster(world->UnmanagedPointer))
{
}

#endif
