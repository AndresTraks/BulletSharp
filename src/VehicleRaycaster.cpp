#include "StdAfx.h"

#include "VehicleRaycaster.h"

VehicleRaycaster::VehicleRaycaster(btVehicleRaycaster* vehicleRaycaster)
{
	_vehicleRaycaster = vehicleRaycaster;
}

btVehicleRaycaster* VehicleRaycaster::UnmanagedPointer::get()
{
	return _vehicleRaycaster;
}
void VehicleRaycaster::UnmanagedPointer::set(btVehicleRaycaster* value)
{
	_vehicleRaycaster = value;
}
