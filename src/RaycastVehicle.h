#pragma once

#include "IAction.h"
#include "VehicleRaycaster.h"

namespace BulletSharp
{
	ref class DynamicsWorld;
	ref class RigidBody;
	ref class WheelInfo;

	public ref class RaycastVehicle : IAction
	{
	public:
		ref class VehicleTuning
		{
		private:
			btScalar _frictionSlip;
			btScalar _maxSuspensionForce;
			btScalar _maxSuspensionTravelCm;
			btScalar _suspensionCompression;
			btScalar _suspensionDamping;
			btScalar _suspensionStiffness;

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

	private:
		array<Vector3>^ _forwardWS;
		array<Vector3>^ _axle;
		array<btScalar>^ _forwardImpulse;
		array<btScalar>^ _sideImpulse;

		List<WheelInfo^>^ _wheelInfo;

		IVehicleRaycaster^ _vehicleRaycaster;
		btScalar _pitchControl;
		btScalar _steeringValue; 
		btScalar _currentVehicleSpeedKmHour;

		int _indexRightAxis;
		int _indexUpAxis;
		int	_indexForwardAxis;

	private:
		RigidBody^ _chassisBody;
		static RigidBody^ _fixedBody;

		static RaycastVehicle();

	public:
		RaycastVehicle(VehicleTuning^ tuning, RigidBody^ chassis, IVehicleRaycaster^ raycaster);

		WheelInfo^ AddWheel(Vector3 connectionPointCS, Vector3 wheelDirectionCS0,
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
		virtual void SetCoordinateSystem(int rightIndex, int upIndex, int forwardIndex);
		void SetPitchControl(btScalar pitch);
		void SetSteeringValue(btScalar steering, int wheel);
		virtual void UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep);
		virtual void UpdateFriction(btScalar timeStep);
		void UpdateSuspension(btScalar deltaTime);
		virtual void UpdateVehicle(btScalar step);
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

		property int UpAxis
		{
			int get();
		}

		property IList<WheelInfo^>^ WheelInfo
		{
			IList<BulletSharp::WheelInfo^>^ get();
		}
	};

	public ref class DefaultVehicleRaycaster : IVehicleRaycaster
	{
	internal:
		btDefaultVehicleRaycaster* _native;

	public:
		!DefaultVehicleRaycaster();
	protected:
		~DefaultVehicleRaycaster();

	public:
		DefaultVehicleRaycaster(DynamicsWorld^ world);

		virtual Object^ CastRay(Vector3 from, Vector3 to, VehicleRaycasterResult^ result);
	};
};
