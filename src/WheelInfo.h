#pragma once

namespace BulletSharp
{
	public ref struct WheelInfo
	{
	private:
		btWheelInfo* _wheelInfo;

	internal:
		WheelInfo(btWheelInfo* wheelInfo);

	public:
		//WheelInfo(WheelInfoConstructionInfo^ ci);

		// UpdateWheel(RigidBody^ chassis, RaycastInfo^ raycastInfo);

		property Vector3 AxleCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Brake
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 ChassisConnectionPointCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property IntPtr ClientInfo
		{
			IntPtr get();
			void set(IntPtr value);
		}

		property btScalar ClippedInvContactDotSuspension
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingCompression
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingRelaxation
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DeltaRotation
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 DirectionCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar EngineForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar FrictionSlip
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool IsFrontWheel
		{
			bool get();
			void set(bool value);
		}

		property btScalar MaxSuspensionTravelCm
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Radius
		{
			btScalar get();
			void set(btScalar value);
		}

		//property BulletSharp::RaycastInfo^ RaycastInfo
		//{
		//	BulletSharp::RaycastInfo^ get();
		//	void set(BulletSharp::RaycastInfo^ value);
		//}

		property btScalar RollInfluence
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Rotation
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SkidInfo
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Steering
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionRelativeVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionRestLength
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionStiffness
		{
			btScalar get();
			void set(btScalar value);
		}

		property Matrix WorldTransform
		{
			Matrix get();
			void set(Matrix value);
		}
	};
}