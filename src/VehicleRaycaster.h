#pragma once

namespace BulletSharp
{
	public ref class VehicleRaycasterResult : System::IDisposable
	{
	internal:
		btVehicleRaycaster::btVehicleRaycasterResult* _native;

	public:
		!VehicleRaycasterResult();
	protected:
		~VehicleRaycasterResult();

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
	};

	public ref class VehicleRaycaster abstract
	{
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
