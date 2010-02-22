#pragma once

namespace BulletSharp
{
	public ref class VehicleRaycaster abstract
	{
		private:
			btVehicleRaycaster* _vehicleRaycaster;

		protected:
			VehicleRaycaster(btVehicleRaycaster* vehicleRaycaster);

		internal:
			property btVehicleRaycaster* UnmanagedPointer
			{
				virtual btVehicleRaycaster* get();
				void set(btVehicleRaycaster* value);
			}
	};
};
