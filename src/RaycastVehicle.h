#pragma once

#include "ActionInterface.h"

namespace BulletSharp
{
	ref class RigidBody;
	ref class VehicleRaycaster;
	ref class WheelInfo;

	public ref class RaycastVehicle : ActionInterface
	{
	public:
		ref class VehicleTuning
		{
		private:
			btRaycastVehicle::btVehicleTuning* _vehicleTuning;

		public:
			VehicleTuning();

		internal:
			property btRaycastVehicle::btVehicleTuning* UnmanagedPointer
			{
				btRaycastVehicle::btVehicleTuning* get();
				void set(btRaycastVehicle::btVehicleTuning* value);
			}
		};

	private:
		RigidBody^ _chassisBody;

	public:
		RaycastVehicle(VehicleTuning^ tuning, RigidBody^ chassis, VehicleRaycaster^ raycaster);

		WheelInfo^ AddWheel(
			Vector3 connectionPointCS0,
			Vector3 wheelDirectionCS0,
			Vector3 wheelAxleCS,
			btScalar suspensionRestLength,
			btScalar wheelRadius,
			VehicleTuning^ tuning,
			bool isFrontWheel
		);

		void ApplyEngineForce(btScalar force, int wheel);
		WheelInfo^ GetWheelInfo(int index);
		btScalar GetSteeringValue(int wheel);
		Matrix GetWheelTransformWS(int wheelIndex);
		//void RayCast(WheelInfo^ wheel);
		void ResetSuspension();
		void SetBrake(btScalar brake, int wheelIndex);
		void SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex);
		//void SetRaycastWheelInfo(int wheelIndex, bool isInContact, Vector3 hitPoint, Vector3 hitNormal, btScalar depth);
		void SetSteeringValue(btScalar steering, int wheel);
		void UpdateFriction(btScalar timeStep);
		void UpdateSuspension(btScalar deltaTime);
		void UpdateVehicle(btScalar step);
		void UpdateWheelTransform(int wheelIndex);
		void UpdateWheelTransform(int wheelIndex, bool interpolatedTransform);

		property Matrix ChassisWorldTransform
		{
			Matrix get();
		}

		property btScalar CurrentSpeedKmHour
		{
			btScalar get();
		}

		property int ForwardAxis
		{
			int get();
		}

		property Vector3 ForwardVector
		{
			Vector3 get();
		}

		property int NumWheels
		{
			int get();
		}

		property btScalar PitchControl
		{
			void set(btScalar value);
		}

		property int RightAxis
		{
			int get();
		}

		property RigidBody^ RigidBody
		{
			BulletSharp::RigidBody^ get();
		}

		property int UpAxis
		{
			int get();
		}

	internal:
		property btRaycastVehicle* UnmanagedPointer
		{
			btRaycastVehicle* get() new;
		}
	};
};
