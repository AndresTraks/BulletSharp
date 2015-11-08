#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	[Flags]
	public enum class SliderFlags
	{
		None = 0,
		CfmDirLinear = BT_SLIDER_FLAGS_CFM_DIRLIN,
		ErpDirLinear = BT_SLIDER_FLAGS_ERP_DIRLIN,
		CfmDirAngular = BT_SLIDER_FLAGS_CFM_DIRANG,
		ErpDirAngular = BT_SLIDER_FLAGS_ERP_DIRANG,
		CfmOrthoLinear = BT_SLIDER_FLAGS_CFM_ORTLIN,
		ErpOrthoLinear = BT_SLIDER_FLAGS_ERP_ORTLIN,
		CfmOrthoAngular = BT_SLIDER_FLAGS_CFM_ORTANG,
		ErpOrthoAngular = BT_SLIDER_FLAGS_ERP_ORTANG,
		CfmLimLinear = BT_SLIDER_FLAGS_CFM_LIMLIN,
		ErpLimLinear = BT_SLIDER_FLAGS_ERP_LIMLIN,
		CfmLimAngular = BT_SLIDER_FLAGS_CFM_LIMANG,
		ErpLimAngular = BT_SLIDER_FLAGS_ERP_LIMANG
	};

	public ref class SliderConstraint : TypedConstraint
	{
	public:
		SliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA,
			Matrix frameInB, bool useLinearReferenceFrameA);
		SliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA);

		void CalculateTransforms(Matrix transA, Matrix transB);
		void GetInfo1NonVirtual(ConstraintInfo1^ info);
		void GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA, Matrix transB,
			Vector3 linVelA, Vector3 linVelB, btScalar rbAinvMass, btScalar rbBinvMass);
		void SetFrames(Matrix frameA, Matrix frameB);
		void TestAngularLimits();
		void TestLinLimits();

		property Vector3 AnchorInA
		{
			Vector3 get();
		}

		property Vector3 AnchorInB
		{
			Vector3 get();
		}

		property btScalar AngularDepth
		{
			btScalar get();
		}

		property btScalar AngularPos
		{
			btScalar get();
		}

		property Matrix CalculatedTransformA
		{
			Matrix get();
		}

		property Matrix CalculatedTransformB
		{
			Matrix get();
		}

		property btScalar DampingDirAngular
		{
			btScalar get();
			void set(btScalar dampingDirAng);
		}

		property btScalar DampingDirLin
		{
			btScalar get();
			void set(btScalar dampingDirLin);
		}

		property btScalar DampingLimAngular
		{
			btScalar get();
			void set(btScalar dampingLimAng);
		}

		property btScalar DampingLimLin
		{
			btScalar get();
			void set(btScalar dampingLimLin);
		}

		property btScalar DampingOrthoAngular
		{
			btScalar get();
			void set(btScalar dampingOrthoAng);
		}

		property btScalar DampingOrthoLin
		{
			btScalar get();
			void set(btScalar dampingOrthoLin);
		}

		property SliderFlags Flags
		{
			SliderFlags get();
		}

		property Matrix FrameOffsetA
		{
			Matrix get();
		}

		property Matrix FrameOffsetB
		{
			Matrix get();
		}

		property btScalar LinDepth
		{
			btScalar get();
		}

		property btScalar LinearPos
		{
			btScalar get();
		}

		property btScalar LowerAngularLimit
		{
			btScalar get();
			void set(btScalar lowerLimit);
		}

		property btScalar LowerLinLimit
		{
			btScalar get();
			void set(btScalar lowerLimit);
		}

		property btScalar MaxAngularMotorForce
		{
			btScalar get();
			void set(btScalar maxAngMotorForce);
		}

		property btScalar MaxLinMotorForce
		{
			btScalar get();
			void set(btScalar maxLinMotorForce);
		}

		property bool PoweredAngularMotor
		{
			bool get();
			void set(bool onOff);
		}

		property bool PoweredLinMotor
		{
			bool get();
			void set(bool onOff);
		}

		property btScalar RestitutionDirAngular
		{
			btScalar get();
			void set(btScalar restitutionDirAng);
		}

		property btScalar RestitutionDirLin
		{
			btScalar get();
			void set(btScalar restitutionDirLin);
		}

		property btScalar RestitutionLimAngular
		{
			btScalar get();
			void set(btScalar restitutionLimAng);
		}

		property btScalar RestitutionLimLin
		{
			btScalar get();
			void set(btScalar restitutionLimLin);
		}

		property btScalar RestitutionOrthoAngular
		{
			btScalar get();
			void set(btScalar restitutionOrthoAng);
		}

		property btScalar RestitutionOrthoLin
		{
			btScalar get();
			void set(btScalar restitutionOrthoLin);
		}

		property btScalar SoftnessDirAngular
		{
			btScalar get();
			void set(btScalar softnessDirAng);
		}

		property btScalar SoftnessDirLin
		{
			btScalar get();
			void set(btScalar softnessDirLin);
		}

		property btScalar SoftnessLimAngular
		{
			btScalar get();
			void set(btScalar softnessLimAng);
		}

		property btScalar SoftnessLimLin
		{
			btScalar get();
			void set(btScalar softnessLimLin);
		}

		property btScalar SoftnessOrthoAngular
		{
			btScalar get();
			void set(btScalar softnessOrthoAng);
		}

		property btScalar SoftnessOrthoLin
		{
			btScalar get();
			void set(btScalar softnessOrthoLin);
		}

		property bool SolveAngularLimit
		{
			bool get();
		}

		property bool SolveLinLimit
		{
			bool get();
		}

		property btScalar TargetAngularMotorVelocity
		{
			btScalar get();
			void set(btScalar targetAngMotorVelocity);
		}

		property btScalar TargetLinMotorVelocity
		{
			btScalar get();
			void set(btScalar targetLinMotorVelocity);
		}

		property btScalar UpperAngularLimit
		{
			btScalar get();
			void set(btScalar upperLimit);
		}

		property btScalar UpperLinLimit
		{
			btScalar get();
			void set(btScalar upperLimit);
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool frameOffsetOnOff);
		}

		property bool UseLinearReferenceFrameA
		{
			bool get();
		}
	};
};
