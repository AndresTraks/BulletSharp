#pragma once

namespace BulletSharp
{
	ref class RigidBody;

	public ref class WheelInfoConstructionInfo
	{
	private:
		Vector3 _chassisConnectionCS;
		btScalar _frictionSlip;
		bool _isFrontWheel;
		btScalar _maxSuspensionForce;
		btScalar _maxSuspensionTravelCm;
		btScalar _suspensionRestLength;
		btScalar _suspensionStiffness;
		Vector3 _wheelAxleCS;
		Vector3 _wheelDirectionCS;
		btScalar _wheelRadius;
		btScalar _wheelsDampingCompression;
		btScalar _wheelsDampingRelaxation;

	public:
		property Vector3 ChassisConnectionCS
		{
			Vector3 get();
			void set(Vector3 value);
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

		property Vector3 WheelAxleCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 WheelDirectionCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar WheelRadius
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WheelsDampingCompression
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WheelsDampingRelaxation
		{
			btScalar get();
			void set(btScalar value);
		}
	};

	public value struct RaycastInfo
	{
	public:
		Vector3 ContactNormalWS;
		Vector3 ContactPointWS;
		Object^ GroundObject;
		Vector3 HardPointWS;
		bool IsInContact;
		btScalar SuspensionLength;
		Vector3 WheelAxleWS;
		Vector3 WheelDirectionWS;
	};

	public ref class WheelInfo
	{
	private:
		btScalar _brake;
		Vector3 _chassisConnectionPointCS;
		Object^ _clientInfo;
		btScalar _clippedInvContactDotSuspension;
		btScalar _deltaRotation;
		btScalar _engineForce;
		btScalar _frictionSlip;
		bool _isFrontWheel;
		btScalar _maxSuspensionForce;
		btScalar _maxSuspensionTravelCm;
		btScalar _rollInfluence;
		btScalar _rotation;
		btScalar _skidInfo;
		btScalar _steering;
		btScalar _suspensionRelativeVelocity;
		btScalar _suspensionRestLength1;
		btScalar _suspensionStiffness;
		Vector3 _wheelAxleCS;
		Vector3 _wheelDirectionCS;
		btScalar _wheelsDampingCompression;
		btScalar _wheelsDampingRelaxation;
		btScalar _wheelsRadius;
		btScalar _wheelsSuspensionForce;
		Matrix	_worldTransform;

	public:
		WheelInfo(WheelInfoConstructionInfo^ ci);

		void UpdateWheel(RigidBody^ chassis, RaycastInfo^ raycastInfo);

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

		property Object^ ClientInfo
		{
			Object^ get();
			void set(Object^ value);
		}

		property btScalar ClippedInvContactDotSuspension
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DeltaRotation
		{
			btScalar get();
			void set(btScalar value);
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

		::RaycastInfo RaycastInfo;

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

		property btScalar SuspensionRelativeVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionRestLength
		{
			btScalar get();
		}

		property btScalar SuspensionRestLength1
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SuspensionStiffness
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 WheelAxleCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 WheelDirectionCS
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar WheelsDampingCompression
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WheelsDampingRelaxation
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WheelsRadius
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar WheelsSuspensionForce
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
};
