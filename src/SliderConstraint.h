#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class SliderConstraint : TypedConstraint
	{
	internal:
		SliderConstraint(btSliderConstraint* constraint);

	public:
		SliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
		SliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA);

		void CalculateTransforms(Matrix transA, Matrix transB);
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
			void set(btScalar value);
		}

		property btScalar DampingDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingLimAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingOrthoAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingOrthoLin
		{
			btScalar get();
			void set(btScalar value);
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
			void set(btScalar value);
		}

		property btScalar LowerLinLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxAngularMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxLinMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool PoweredAngularMotor
		{
			bool get();
			void set(bool value);
		}

		property bool PoweredLinMotor
		{
			bool get();
			void set(bool value);
		}

		property btScalar RestitutionDirAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionLimAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionOrthoAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionOrthoLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessDirAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessLimAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessOrthoAngular
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessOrthoLin
		{
			btScalar get();
			void set(btScalar value);
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
			void set(btScalar value);
		}

		property btScalar TargetLinMotorVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar UpperAngularLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar UpperLinLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool UseFrameOffset
		{
			bool get();
			void set(bool value);
		}

		property bool UseLinearReferenceFrameA
		{
			bool get();
		}
	};
};
