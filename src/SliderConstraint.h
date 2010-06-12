#pragma once

// Fully implemented as of 12 May 2010

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class SliderConstraint : TypedConstraint
	{
	internal:
		SliderConstraint(btSliderConstraint* constraint);

	public:
		SliderConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA);
		SliderConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameA);

		void CalculateTransforms(Matrix transA, Matrix transB);
		void TestAngLimits();
		void TestLinLimits();

		property Vector3 AnchorInA
		{
			Vector3 get();
		}

		property Vector3 AnchorInB
		{
			Vector3 get();
		}

		property btScalar AngDepth
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

		property btScalar DampingDirAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingLimAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar DampingOrthoAng
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

		property btScalar LowerAngLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar LowerLinLimit
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxAngMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar MaxLinMotorForce
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool PoweredAngMotor
		{
			bool get();
			void set(bool value);
		}

		property bool PoweredLinMotor
		{
			bool get();
			void set(bool value);
		}

		property btScalar RestitutionDirAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionLimAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionOrthoAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RestitutionOrthoLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessDirAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessDirLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessLimAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessLimLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessOrthoAng
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar SoftnessOrthoLin
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool SolveAngLimit
		{
			bool get();
		}

		property bool SolveLinLimit
		{
			bool get();
		}

		property btScalar TargetAngMotorVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar TargetLinMotorVelocity
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar UpperAngLimit
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

	internal:
		property btSliderConstraint* UnmanagedPointer
		{
			btSliderConstraint* get() new;
		}
	};
};
