#pragma once

#include "IActionInterface.h"
#include "VehicleRaycaster.h"

namespace BulletSharp
{
	ref class DynamicsWorld;
	ref class RigidBody;
	ref class WheelInfo;
	ref class AlignedWheelInfoArray;

	public ref class RaycastVehicle : IActionInterface,  ITrackingDisposable
	{
	public:
		ref class VehicleTuning : IDisposable
		{
		internal:
			btRaycastVehicle::btVehicleTuning* _native;

		public:
			!VehicleTuning();
		protected:
			~VehicleTuning();

		public:
			VehicleTuning();

			property btScalar FrictionSlip
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar MaxSuspensionForce
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar MaxSuspensionTravelCm
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SuspensionCompression
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SuspensionDamping
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SuspensionStiffness
			{
				btScalar get();
				void set(btScalar value);
			}
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btRaycastVehicle* _native;

	private:
		RigidBody^ _chassisBody;
		RaycastVehicle::VehicleTuning^ _tuning;
		VehicleRaycaster^ _raycaster;

	public:
		!RaycastVehicle();
	protected:
		~RaycastVehicle();

	public:
		RaycastVehicle(VehicleTuning^ tuning, RigidBody^ chassis, VehicleRaycaster^ raycaster);

		WheelInfo^ AddWheel(Vector3 connectionPointCS0, Vector3 wheelDirectionCS0,
			Vector3 wheelAxleCS, btScalar suspensionRestLength, btScalar wheelRadius,
			VehicleTuning^ tuning, bool isFrontWheel);
		void ApplyEngineForce(btScalar force, int wheel);
#ifndef DISABLE_DEBUGDRAW
		virtual void DebugDraw(IDebugDraw^ debugDrawer);
#endif
		btScalar GetSteeringValue(int wheel);
		WheelInfo^ GetWheelInfo(int index);
		Matrix GetWheelTransformWS(int wheelIndex);
		btScalar RayCast(WheelInfo^ wheel);
		void ResetSuspension();
		void SetBrake(btScalar brake, int wheelIndex);
		void SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex);
		void SetPitchControl(btScalar pitch);
		void SetSteeringValue(btScalar steering, int wheel);
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);
		void UpdateFriction(btScalar timeStep);
		void UpdateSuspension(btScalar deltaTime);
		void UpdateVehicle(btScalar step);
		void UpdateWheelTransform(int wheelIndex, bool interpolatedTransform);
		void UpdateWheelTransform(int wheelIndex);
		void UpdateWheelTransformsWS(WheelInfo^ wheel, bool interpolatedTransform);
		void UpdateWheelTransformsWS(WheelInfo^ wheel);

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

		property bool IsDisposed
		{
			virtual bool get();
		}

		property int NumWheels
		{
			int get();
		}

		property int RightAxis
		{
			int get();
		}

		property RigidBody^ RigidBody
		{
			BulletSharp::RigidBody^ get();
		}

		property RaycastVehicle::VehicleTuning^ Tuning
		{
			RaycastVehicle::VehicleTuning^ get();
		}

		property VehicleRaycaster^ Raycaster
		{
			VehicleRaycaster^ get();
		}

		property int UpAxis
		{
			int get();
		}

		property AlignedWheelInfoArray^ WheelInfo
		{
			AlignedWheelInfoArray^ get();
		}
	};

	public ref class DefaultVehicleRaycaster : VehicleRaycaster
	{
	public:
		DefaultVehicleRaycaster(DynamicsWorld^ world);
	};
};
