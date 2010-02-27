#include "StdAfx.h"

#include "DefaultVehicleRaycaster.h"
#include "DynamicsWorld.h"

DefaultVehicleRaycaster::DefaultVehicleRaycaster(DynamicsWorld^ world)
: VehicleRaycaster(new btDefaultVehicleRaycaster(world->UnmanagedPointer))
{
}
