#pragma once

namespace BulletSharp
{
	ref class RigidBody;
	ref class ScalarArray;
	#ifndef DISABLE_SERIALIZE
	ref class Serializer;
	#endif

	public ref class JointFeedback
	{
	internal:
		btJointFeedback* _native;

		~JointFeedback();
		!JointFeedback();

	public:
		JointFeedback();

		property Vector3 AppliedForceBodyA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedForceBodyB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedTorqueBodyA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedTorqueBodyB
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class TypedConstraint abstract : ITrackingDisposable
	{
	public:
		ref class ConstraintInfo1
		{
		internal:
			btTypedConstraint::btConstraintInfo1* _native;

			~ConstraintInfo1();
			!ConstraintInfo1();

		public:
			ConstraintInfo1();

			property int Nub
			{
				int get();
				void set(int value);
			}

			property int NumConstraintRows
			{
				int get();
				void set(int value);
			}
		};

		ref class ConstraintInfo2
		{
		internal:
			btTypedConstraint::btConstraintInfo2* _native;

		private:
			ScalarArray^ _cfm;
			ScalarArray^ _constraintError;
			ScalarArray^ _j1angularAxis;
			ScalarArray^ _j1linearAxis;
			ScalarArray^ _j2angularAxis;
			ScalarArray^ _j2linearAxis;
			ScalarArray^ _lowerLimit;
			ScalarArray^ _upperLimit;

			~ConstraintInfo2();
			!ConstraintInfo2();

		public:
			ConstraintInfo2();

			property ScalarArray^ Cfm
			{
				ScalarArray^ get();
			}

			property ScalarArray^ ConstraintError
			{
				ScalarArray^ get();
			}

			property btScalar Damping
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Erp
			{
				btScalar get();
				void set(btScalar value);
			}
			/*
			property int^ Findex
			{
				int^ get();
				void set(int^ value);
			}
			*/
			property btScalar Fps
			{
				btScalar get();
				void set(btScalar value);
			}

			property ScalarArray^ J1angularAxis
			{
				ScalarArray^ get();
			}

			property ScalarArray^ J1linearAxis
			{
				ScalarArray^ get();
			}

			property ScalarArray^ J2angularAxis
			{
				ScalarArray^ get();
			}

			property ScalarArray^ J2linearAxis
			{
				ScalarArray^ get();
			}

			property ScalarArray^ LowerLimit
			{
				ScalarArray^ get();
			}

			property int NumIterations
			{
				int get();
				void set(int value);
			}

			property int Rowskip
			{
				int get();
				void set(int value);
			}

			property ScalarArray^ UpperLimit
			{
				ScalarArray^ get();
			}
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		bool _isDisposed;
		Object^ _userObject;
		JointFeedback^ _jointFeedback;
		static RigidBody^ _fixedBody;

	protected:
		RigidBody^ _rigidBodyA;
		RigidBody^ _rigidBodyB;

	internal:
		btTypedConstraint* _native;
		bool _preventDelete;

		TypedConstraint(btTypedConstraint* native);

		static TypedConstraint^ GetManaged(btTypedConstraint* native);

		!TypedConstraint();
		~TypedConstraint();

	public:
		void BuildJacobian();
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void EnableFeedback(bool needsFeedback);
		static RigidBody^ GetFixedBody();
		void GetInfo1(ConstraintInfo1^ info);
		void GetInfo2(ConstraintInfo2^ info);
		btScalar GetParam(ConstraintParam num, int axis);
		btScalar GetParam(ConstraintParam num);
#ifndef DISABLE_INTERNAL
		btScalar InternalGetAppliedImpulse();
#endif
		void InternalSetAppliedImpulse(btScalar appliedImpulse);
#ifndef DISABLE_SERIALIZE
		String^ Serialize(IntPtr dataBuffer, Serializer^ serializer);
#endif
		void SetParam(ConstraintParam num, btScalar value, int axis);
		void SetParam(ConstraintParam num, btScalar value);
		//void SetupSolverConstraint(ConstraintArray^ ca, int solverBodyA, int solverBodyB,
		//	btScalar timeStep);

		property btScalar AppliedImpulse
		{
			btScalar get();
		}

		property btScalar BreakingImpulseThreshold
		{
			btScalar get();
			void set(btScalar threshold);
		}

		property TypedConstraintType ConstraintType
		{
			TypedConstraintType get();
		}

		property btScalar DebugDrawSize
		{
			btScalar get();
			void set(btScalar dbgDrawSize);
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsEnabled
		{
			bool get();
			void set(bool enabled);
		}

		property BulletSharp::JointFeedback^ JointFeedback
		{
			BulletSharp::JointFeedback^ get();
			void set(BulletSharp::JointFeedback^ jointFeedback);
		}

		property bool NeedsFeedback
		{
			bool get();
			void set(bool value);
		}

		property int OverrideNumSolverIterations
		{
			int get();
			void set(int overideNumIterations);
		}

		property RigidBody^ RigidBodyA
		{
			RigidBody^ get();
		}

		property RigidBody^ RigidBodyB
		{
			RigidBody^ get();
		}

		property int Uid
		{
			int get();
		}

		// UserConstraintId/UserConstraintPtr union implemented as UserObject
		property Object^ UserObject
		{
			Object^ get();
			void set(Object^ value);
		}

		property int UserConstraintType
		{
			int get();
			void set(int value);
		}

	internal:
		property btTypedConstraint* UnmanagedPointer
		{
			btTypedConstraint* get();
			void set(btTypedConstraint* value);
		}
	};

#ifdef _BT_USE_CENTER_LIMIT_
#ifdef IN_PARALLELL_SOLVER
	public ref class AngularLimit
	{
	internal:
		btAngularLimit* _native;

	private:
		bool _preventDelete;

	internal:
		AngularLimit(btAngularLimit* native, bool preventDelete);

		~AngularLimit();
		!AngularLimit();

	public:
		AngularLimit();

		void Fit(btScalar% angle);
		void Set(btScalar low, btScalar high, btScalar softness, btScalar biasFactor,
			btScalar relaxationFactor);
		void Set(btScalar low, btScalar high, btScalar softness, btScalar biasFactor);
		void Set(btScalar low, btScalar high, btScalar softness);
		void Set(btScalar low, btScalar high);
		void Test(btScalar angle);

		property btScalar BiasFactor
		{
			btScalar get();
		}

		property btScalar Correction
		{
			btScalar get();
		}

		property btScalar Error
		{
			btScalar get();
		}

		property btScalar HalfRange
		{
			btScalar get();
		}

		property btScalar High
		{
			btScalar get();
		}

		property bool IsLimit
		{
			bool get();
		}

		property btScalar Low
		{
			btScalar get();
		}

		property btScalar RelaxationFactor
		{
			btScalar get();
		}

		property btScalar Sign
		{
			btScalar get();
		}

		property btScalar Softness
		{
			btScalar get();
		}
	};
#endif
#endif
};
