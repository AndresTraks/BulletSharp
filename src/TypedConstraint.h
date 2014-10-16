#pragma once

namespace BulletSharp
{
	ref class RigidBody;
	#ifndef DISABLE_SERIALIZE
	ref class Serializer;
	#endif

	public ref class JointFeedback : IDisposable
	{
	internal:
		btJointFeedback* _native;
		JointFeedback(btJointFeedback* native);
		JointFeedback(btJointFeedback* native, bool preventDelete);

	public:
		bool _preventDelete;

	public:
		!JointFeedback();
	protected:
		~JointFeedback();

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
		ref class ConstraintInfo1 : IDisposable
		{
		internal:
			btTypedConstraint::btConstraintInfo1* _native;
			ConstraintInfo1(btTypedConstraint::btConstraintInfo1* native, bool preventDelete);

		public:
			bool _preventDelete;

		public:
			!ConstraintInfo1();
		protected:
			~ConstraintInfo1();

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

		ref class ConstraintInfo2 : IDisposable
		{
		internal:
			btTypedConstraint::btConstraintInfo2* _native;
			ConstraintInfo2(btTypedConstraint::btConstraintInfo2* native, bool preventDelete);

		public:
			bool _preventDelete;

		public:
			!ConstraintInfo2();
		protected:
			~ConstraintInfo2();

		public:
			ConstraintInfo2();
			/*
			property float^ Cfm
			{
				float^ get();
				void set(float^ value);
			}

			property float^ ConstraintError
			{
				float^ get();
				void set(float^ value);
			}
			*/
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
			/*
			property float^ J1angularAxis
			{
				float^ get();
				void set(float^ value);
			}

			property float^ J1linearAxis
			{
				float^ get();
				void set(float^ value);
			}

			property float^ J2angularAxis
			{
				float^ get();
				void set(float^ value);
			}

			property float^ J2linearAxis
			{
				float^ get();
				void set(float^ value);
			}

			property float^ LowerLimit
			{
				float^ get();
				void set(float^ value);
			}
			*/
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
			/*
			property float^ UpperLimit
			{
				float^ get();
				void set(float^ value);
			}
			*/
		};

	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		Object^ _userObject;
		JointFeedback^ _jointFeedback;

	internal:
		btTypedConstraint* _native;
		bool _preventDelete;

		TypedConstraint(btTypedConstraint* typedConstraint);
		static TypedConstraint^ GetManaged(btTypedConstraint* native);

	public:
		!TypedConstraint();
	protected:
		~TypedConstraint();

	public:
		void BuildJacobian();
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void EnableFeedback(bool needsFeedback);
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

		property RigidBody^ FixedBody
		{
			static RigidBody^ get();
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
	public ref class AngularLimit : IDisposable
	{
	internal:
		btAngularLimit* _native;
		AngularLimit(btAngularLimit* native, bool preventDelete);

	public:
		bool _preventDelete;

	public:
		!AngularLimit();
	protected:
		~AngularLimit();

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
