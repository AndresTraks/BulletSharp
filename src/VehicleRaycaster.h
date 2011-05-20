#pragma once

namespace BulletSharp
{
	public ref class VehicleRaycaster abstract
	{
	public:
		ref class VehicleRaycasterResult
		{
		private:
			btVehicleRaycaster::btVehicleRaycasterResult* _result;

		public:
			VehicleRaycasterResult();

			property btScalar DistFraction
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 HitNormalInWorld
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 HitPointInWorld
			{
				Vector3 get();
				void set(Vector3 value);
			}

		internal:
			property btVehicleRaycaster::btVehicleRaycasterResult* UnmanagedPointer
			{
				virtual btVehicleRaycaster::btVehicleRaycasterResult* get();
				void set(btVehicleRaycaster::btVehicleRaycasterResult* value);
			}
		};

	private:
		btVehicleRaycaster* _vehicleRaycaster;

	internal:
		VehicleRaycaster(btVehicleRaycaster* vehicleRaycaster);

	public:
		Object^ CastRay(Vector3 from, Vector3 to, VehicleRaycasterResult^ result);

	internal:
		property btVehicleRaycaster* UnmanagedPointer
		{
			virtual btVehicleRaycaster* get();
			void set(btVehicleRaycaster* value);
		}
	};
};
