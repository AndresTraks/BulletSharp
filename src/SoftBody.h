#pragma once

#include "CollisionObject.h"
#include "ConvexShape.h"

namespace BulletSharp
{
	ref class AlignedIntArray;
	ref class AlignedScalarArray;
	ref class AlignedVector3Array;
	ref class AlignedCollisionObjectArray;
	ref class BroadphaseInterface;
	ref class CollisionObjectWrapper;
	ref class Dbvt;
	ref class DbvtNode;
	ref class Dispatcher;
	ref class ScalarArray;
	ref class RigidBody;
	ref class SparseSdf;
	ref class Vector3Array;

	namespace SoftBody
	{
		class AJointIControlWrapper;
		class ImplicitFnWrapper;
		ref class AlignedAnchorArray;
		ref class AlignedClusterArray;
		ref class AlignedFaceArray;
		ref class AlignedJointArray;
		ref class AlignedLinkArray;
		ref class AlignedMaterialArray;
		ref class AlignedNodeArray;
		ref class AlignedNodePtrArray;
		ref class AlignedNoteArray;
		ref class AlignedRigidContactArray;
		ref class AlignedSoftBodyArray;
		ref class AlignedSoftContactArray;
		ref class AlignedTetraArray;
		ref class AlignedPSolverArray;
		ref class AlignedVSolverArray;
		ref class BodyArray;
		ref class Cluster;
		ref class Feature;
		ref class Impulse;
		ref class Material;
		ref class Node;
		ref class NodePtrArray;
		ref class Scti;
		ref class SoftBody;
		ref class SoftBodySolver;

		public ref class SoftBodyCollisionShape : ConvexShape
		{
		internal:
			SoftBodyCollisionShape(btConvexShape* native);
		};

		public ref class SoftBodyWorldInfo
		{
		internal:
			btSoftBodyWorldInfo* _native;

		private:
			bool _preventDelete;
			BroadphaseInterface^ _broadphase;
			Dispatcher^ _dispatcher;
			SparseSdf^ _sparseSdf;

		internal:
			SoftBodyWorldInfo(btSoftBodyWorldInfo* native);

			~SoftBodyWorldInfo();
			!SoftBodyWorldInfo();

		public:
			SoftBodyWorldInfo();

			property btScalar AirDensity
			{
				btScalar get();
				void set(btScalar value);
			}

			property BroadphaseInterface^ Broadphase
			{
				BroadphaseInterface^ get();
				void set(BroadphaseInterface^ value);
			}

			property BulletSharp::Dispatcher^ Dispatcher
			{
				BulletSharp::Dispatcher^ get();
				void set(BulletSharp::Dispatcher^ value);
			}

			property Vector3 Gravity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar MaxDisplacement
			{
				btScalar get();
				void set(btScalar value);
			}

			property BulletSharp::SparseSdf^ SparseSdf
			{
				BulletSharp::SparseSdf^ get();
			}

			property btScalar WaterDensity
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 WaterNormal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar WaterOffset
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public enum class AeroModel
		{
			VPoint = btSoftBody::eAeroModel::V_Point,
			VTwoSided = btSoftBody::eAeroModel::V_TwoSided,
			VTwoSidedLiftDrag = btSoftBody::eAeroModel::V_TwoSidedLiftDrag,
			VOneSided = btSoftBody::eAeroModel::V_OneSided,
			FTwoSided = btSoftBody::eAeroModel::F_TwoSided,
			FTwoSidedLiftDrag = btSoftBody::eAeroModel::F_TwoSidedLiftDrag,
			FOneSided = btSoftBody::eAeroModel::F_OneSided,
			End = btSoftBody::eAeroModel::END
		};

		[Flags]
		public enum class EFeature
		{
			None = btSoftBody::eFeature::None,
			Node = btSoftBody::eFeature::Node,
			Link = btSoftBody::eFeature::Link,
			Face = btSoftBody::eFeature::Face,
			Tetra = btSoftBody::eFeature::Tetra,
			End = btSoftBody::eFeature::END
		};

		[Flags]
		public enum class FCollisions
		{
			RvsMask = btSoftBody::fCollision::RVSmask,
			SdfRS = btSoftBody::fCollision::SDF_RS,
			CLRS = btSoftBody::fCollision::CL_RS,
			SvsMask = btSoftBody::fCollision::SVSmask,
			VFSS = btSoftBody::fCollision::VF_SS,
			CLSS = btSoftBody::fCollision::CL_SS,
			CLSelf = btSoftBody::fCollision::CL_SELF,
			Default = btSoftBody::fCollision::Default,
			End = btSoftBody::fCollision::END
		};

		[Flags]
		public enum class FMaterial
		{
			DebugDraw = btSoftBody::fMaterial::DebugDraw,
			Default = btSoftBody::fMaterial::Default,
			End = btSoftBody::fMaterial::END
		};

		[Flags]
		public enum class ESolverPresets
		{
			Positions = btSoftBody::eSolverPresets::Positions,
			Velocities = btSoftBody::eSolverPresets::Velocities,
			Default = btSoftBody::eSolverPresets::Default,
			End = btSoftBody::eSolverPresets::END
		};

		public ref class Joint abstract
		{
		public:
			ref class Specs abstract
			{
			internal:
				btSoftBody::Joint::Specs* _native;

				Specs(btSoftBody::Joint::Specs* native);

				~Specs();
				!Specs();

			public:
				property btScalar Cfm
				{
					btScalar get();
					void set(btScalar value);
				}

				property btScalar Erp
				{
					btScalar get();
					void set(btScalar value);
				}

				property btScalar Split
				{
					btScalar get();
					void set(btScalar value);
				}
			};

			enum class JointType
			{
				Linear, Angular, Contact
			};

		internal:
			btSoftBody::Joint* _native;

		private:
			BodyArray^ _bodies;
			Vector3Array^ _refs;

		internal:
			Joint(btSoftBody::Joint* native);

		public:
			void Prepare(btScalar deltaTime, int iterations);
			void Solve(btScalar deltaTime, btScalar sor);
			void Terminate(btScalar deltaTime);

			property BodyArray^ Bodies
			{
				BodyArray^ get();
			}

			property btScalar Cfm
			{
				btScalar get();
				void set(btScalar value);
			}

			property bool Delete
			{
				bool get();
				void set(bool value);
			}

			property Vector3 Drift
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar Erp
			{
				btScalar get();
				void set(btScalar value);
			}

			property Matrix MassMatrix
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3Array^ Refs
			{
				Vector3Array^ get();
			}

			property Vector3 SDrift
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar Split
			{
				btScalar get();
				void set(btScalar value);
			}

			property JointType Type
			{
				JointType get();
			}
		};

		public ref class AJoint : Joint
		{
		public:
			ref class IControl
			{
			private:
				[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
				delegate void PrepareUnmanagedDelegate(IntPtr aJoint);
				[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
				delegate btScalar SpeedUnmanagedDelegate(IntPtr aJoint, btScalar current);

				PrepareUnmanagedDelegate^ _prepare;
				SpeedUnmanagedDelegate^ _speed;

				void PrepareUnmanaged(IntPtr aJoint);
				btScalar SpeedUnmanaged(IntPtr aJoint, btScalar current);

				static AJoint::IControl^ _default;
				bool _preventDelete;

			internal:
				btSoftBody::AJoint::IControl* _native;

				IControl(btSoftBody::AJoint::IControl* native, bool preventDelete);

				~IControl();
				!IControl();

			public:
				IControl();

				static IControl^ Default();
				virtual void Prepare(AJoint^ joint);
				virtual btScalar Speed(AJoint^ joint, btScalar current);
			};

			ref class Specs : Joint::Specs
			{
				AJoint::IControl^ _iControl;

			public:
				Specs();

				property Vector3 Axis
				{
					Vector3 get();
					void set(Vector3 value);
				}

				property IControl^ Control
				{
					AJoint::IControl^ get();
					void set(AJoint::IControl^ value);
				}
			};

		internal:
			AJoint::IControl^ _iControl;

		private:
			Vector3Array^ _axis;

		internal:
			AJoint(btSoftBody::AJoint* native);

		public:
			property Vector3Array^ Axis
			{
				Vector3Array^ get();
			}

			property IControl^ Control
			{
				AJoint::IControl^ get();
				void set(AJoint::IControl^ value);
			}
		};

		typedef void (*pIControl_Prepare)(btSoftBody::AJoint* aJoint);
		typedef btScalar (*pIControl_Speed)(btSoftBody::AJoint* aJoint, btScalar current);

		class AJointIControlWrapper : public btSoftBody::AJoint::IControl
		{
		private:
			pIControl_Prepare _prepareCallback;
			pIControl_Speed _speedCallback;

		public:
			AJointIControlWrapper(pIControl_Prepare prepareCallback, pIControl_Speed speedCallback);

			virtual void Prepare(btSoftBody::AJoint* joint);
			virtual btScalar Speed(btSoftBody::AJoint* joint, btScalar current);
		};

		public ref class Anchor
		{
		internal:
			btSoftBody::Anchor* _native;


		private:
			BulletSharp::SoftBody::Node^ _node;

		internal:
			Anchor(btSoftBody::Anchor* native);

		public:
			property RigidBody^ Body
			{
				RigidBody^ get();
				void set(RigidBody^ value);
			}

			property Matrix C0
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 C1
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar C2
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Influence
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 Local
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property BulletSharp::SoftBody::Node^ Node
			{
				BulletSharp::SoftBody::Node^ get();
				void set(BulletSharp::SoftBody::Node^ value);
			}
		};

		public ref class Body
		{
		internal:
			btSoftBody::Body* _native;

		private:
			Cluster^ _soft;

		internal:
			Body(btSoftBody::Body* native);

			~Body();
			!Body();

		public:
			Body();
			Body(CollisionObject^ colObj);
			Body(Cluster^ p);

			void Activate();
			void ApplyAImpulse(Impulse^ impulse);
			void ApplyDAImpulse(Vector3 impulse);
			void ApplyDCImpulse(Vector3 impulse);
			void ApplyDImpulse(Vector3 impulse, Vector3 rPos);
			void ApplyImpulse(Impulse^ impulse, Vector3 rPos);
			void ApplyVAImpulse(Vector3 impulse);
			void ApplyVImpulse(Vector3 impulse, Vector3 rPos);
			Vector3 GetAngularVelocity(Vector3 rPos);
			Vector3 Velocity(Vector3 rPos);

			property Vector3 AngularVelocity
			{
				Vector3 get();
			}

			property BulletSharp::CollisionObject^ CollisionObject
			{
				BulletSharp::CollisionObject^ get();
				void set(BulletSharp::CollisionObject^ value);
			}

			property btScalar InvMass
			{
				btScalar get();
			}

			property Matrix InvWorldInertia
			{
				Matrix get();
			}

			property Vector3 LinearVelocity
			{
				Vector3 get();
			}

			property RigidBody^ Rigid
			{
				RigidBody^ get();
				void set(RigidBody^ value);
			}

			property Cluster^ Soft
			{
				Cluster^ get();
				void set(Cluster^ value);
			}

			property Matrix XForm
			{
				Matrix get();
			}
		};

		public ref class CJoint : Joint
		{
		internal:
			CJoint(btSoftBody::CJoint* native);

		private:
			Vector3Array^ _rPos;

		public:
			property btScalar Friction
			{
				btScalar get();
				void set(btScalar value);
			}

			property int Life
			{
				int get();
				void set(int value);
			}

			property int MaxLife
			{
				int get();
				void set(int value);
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3Array^ RPos
			{
				Vector3Array^ get();
			}
		};

		[DebuggerDisplay("Index = {ClusterIndex}")]
		public ref class Cluster
		{
		internal:
			btSoftBody::Cluster* _native;

		private:
			Vector3Array^ _dImpulses;
			AlignedVector3Array^ _frameRefs;
#ifndef DISABLE_DBVT
			DbvtNode^ _leaf;
#endif
			AlignedScalarArray^ _masses;
			AlignedNodePtrArray^ _nodes;
			Vector3Array^ _vImpulses;

		internal:
			Cluster(btSoftBody::Cluster* native);

		public:
			property btScalar AngularDamping
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 AV
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property int ClusterIndex
			{
				int get();
				void set(int value);
			}

			property bool Collide
			{
				bool get();
				void set(bool value);
			}

			property Vector3 Com
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property bool ContainsAnchor
			{
				bool get();
				void set(bool value);
			}

			property Vector3Array^ DImpulses
			{
				Vector3Array^ get();
			}

			property AlignedVector3Array^ FrameRefs
			{
				AlignedVector3Array^ get();
			}

			property Matrix FrameTransform
			{
				Matrix get();
				void set(Matrix value);
			}

			property btScalar IDMass
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar IMass
			{
				btScalar get();
				void set(btScalar value);
			}

			property Matrix InvWI
			{
				Matrix get();
				void set(Matrix value);
			}

#ifndef DISABLE_DBVT
			property DbvtNode^ Leaf
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
#endif

			property btScalar LinearDamping
			{
				btScalar get();
				void set(btScalar value);
			}

			property Matrix Locii
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 LV
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property AlignedScalarArray^ Masses
			{
				AlignedScalarArray^ get();
			}

			property btScalar Matching
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar MaxSelfCollisionImpulse
			{
				btScalar get();
				void set(btScalar value);
			}

			property int NDImpulses
			{
				int get();
			}

			property btScalar NodeDamping
			{
				btScalar get();
				void set(btScalar value);
			}

			property AlignedNodePtrArray^ Nodes
			{
				AlignedNodePtrArray^ get();
			}

			property int NVImpulses
			{
				int get();
			}

			property btScalar SelfCollisionImpulseFactor
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3Array^ VImpulses
			{
				Vector3Array^ get();
			}
		};

		public ref class Config
		{
		internal:
			btSoftBody::Config* _native;

		private:
			AlignedPSolverArray^ _dSequence;
			AlignedPSolverArray^ _pSequence;
			AlignedVSolverArray^ _vSequence;

		internal:
			Config(btSoftBody::Config* native);

		public:
			property AeroModel AeroModel
			{
				BulletSharp::SoftBody::AeroModel get();
				void set(BulletSharp::SoftBody::AeroModel value);
			}

			property btScalar Ahr
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Chr
			{
				btScalar get();
				void set(btScalar value);
			}

			property int CIterations
			{
				int get();
				void set(int value);
			}

			property FCollisions Collisions
			{
				FCollisions get();
				void set(FCollisions value);
			}

			property btScalar DF
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar DG
			{
				btScalar get();
				void set(btScalar value);
			}

			property int DIterations
			{
				int get();
				void set(int value);
			}

			property btScalar DP
			{
				btScalar get();
				void set(btScalar value);
			}

			property AlignedPSolverArray^ DSequence
			{
				AlignedPSolverArray^ get();
			}

			property btScalar Khr
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar LF
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar MaxVolume
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar MT
			{
				btScalar get();
				void set(btScalar value);
			}

			property int PIterations
			{
				int get();
				void set(int value);
			}

			property btScalar PR
			{
				btScalar get();
				void set(btScalar value);
			}

			property AlignedPSolverArray^ PSequence
			{
				AlignedPSolverArray^ get();
			}

			property btScalar Shr
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SkhrCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SrhrCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SshrCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SKSplitCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SRSplitCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar SSSplitCl
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar TimeScale
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar VC
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar VCF
			{
				btScalar get();
				void set(btScalar value);
			}

			property int VIterations
			{
				int get();
				void set(int value);
			}

			property AlignedVSolverArray^ VSequence
			{
				AlignedVSolverArray^ get();
			}
		};

		public ref class ContactInfo
		{
		internal:
			btSoftBody::sCti* _native;

		private:
			bool _preventDelete;

		internal:
			ContactInfo(btSoftBody::sCti* native, bool preventDelete);

			~ContactInfo();
			!ContactInfo();

		public:
			ContactInfo();

			property CollisionObject^ CollisionObject
			{
				BulletSharp::CollisionObject^ get();
				void set(BulletSharp::CollisionObject^ value);
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar Offset
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public ref class Element
		{
		internal:
			btSoftBody::Element* _native;

			Element(btSoftBody::Element* native);

		public:
			property IntPtr Tag
			{
				IntPtr get();
				void set(IntPtr value);
			}
		};

		public ref class Feature : Element
		{
			BulletSharp::SoftBody::Material^ _material;

		internal:
			Feature(btSoftBody::Feature* native);

		public:
			property BulletSharp::SoftBody::Material^ Material
			{
				BulletSharp::SoftBody::Material^ get();
				void set(BulletSharp::SoftBody::Material^ value);
			}
		};

		public ref class Face : Feature
		{
#ifndef DISABLE_DBVT
			DbvtNode^ _leaf;
#endif
			NodePtrArray^ _n;

		internal:
			Face(btSoftBody::Face* native);

		public:
#ifndef DISABLE_DBVT
			property DbvtNode^ Leaf
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
#endif
			property NodePtrArray^ N
			{
				NodePtrArray^ get();
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar RestArea
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public ref class ImplicitFn abstract
		{
		private:
			[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
			delegate btScalar EvalUnmanagedDelegate(IntPtr x);

			EvalUnmanagedDelegate^ _eval;

			btScalar EvalUnmanaged(IntPtr x);

		internal:
			ImplicitFnWrapper* _native;

			~ImplicitFn();
			!ImplicitFn();

		protected:
			ImplicitFn();

		public:
			virtual btScalar Eval(Vector3 x) = 0;
		};

		typedef btScalar (*pImplicitFn_Eval)(const btScalar* x);

		class ImplicitFnWrapper : public btSoftBody::ImplicitFn
		{
		private:
			pImplicitFn_Eval _evalCallback;

		public:
			ImplicitFnWrapper(pImplicitFn_Eval evalCallback);

			virtual btScalar Eval(const btVector3& x);
		};

		public ref class Impulse
		{
		internal:
			btSoftBody::Impulse* _native;

			Impulse(btSoftBody::Impulse* native);

			~Impulse();
			!Impulse();

		public:
			Impulse();

			static Impulse^ operator-(Impulse^ i);
			static Impulse^ operator*(Impulse^ i, btScalar x);

			property bool AsDrift
			{
				bool get();
				void set(bool value);
			}

			property bool AsVelocity
			{
				bool get();
				void set(bool value);
			}

			property Vector3 Drift
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 Velocity
			{
				Vector3 get();
				void set(Vector3 value);
			}
		};

		public ref class Link : Feature
		{
			NodePtrArray^ _nodes;

		internal:
			Link(btSoftBody::Link* native);

		public:
			property btScalar C0
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar C1
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar C2
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 C3
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property bool IsBending
			{
				bool get();
				void set(bool value);
			}

			property NodePtrArray^ Nodes
			{
				NodePtrArray^ get();
			}

			property btScalar RestLength
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public ref class LJoint : Joint
		{
		public:
			[DebuggerDisplay("Position = {Position}")]
			ref class Specs : Joint::Specs
			{
			public:
				Specs();

				property Vector3 Position
				{
					Vector3 get();
					void set(Vector3 value);
				}
			};

		private:
			Vector3Array^ _rPos;

		internal:
			LJoint(btSoftBody::LJoint* native);

		public:
			property Vector3Array^ RPos
			{
				Vector3Array^ get();
			}
		};

		// Not to be confused with Mogre::Material
		public ref class Material : Element
		{
		internal:
			Material(btSoftBody::Material* native);

		public:
			property btScalar Ast
			{
				btScalar get();
				void set(btScalar value);
			}

			property FMaterial Flags
			{
				FMaterial get();
				void set(FMaterial value);
			}

			property btScalar Lst
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Vst
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		// Not to be confused with Mogre::Node
		[DebuggerDisplay("{X}")]
		public ref class Node : Feature
		{
#ifndef DISABLE_DBVT
			DbvtNode^ _leaf;
#endif

		internal:
			Node(btSoftBody::Node* native);

		public:
			void GetNormal([Out] Vector3% normal);
			void GetX([Out] Vector3% x);

			property btScalar Area
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 Force
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar InverseMass
			{
				btScalar get();
				void set(btScalar value);
			}

			property bool IsAttached
			{
				bool get();
				void set(bool value);
			}

#ifndef DISABLE_DBVT
			property DbvtNode^ Leaf
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
#endif

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 Q
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 Velocity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 X
			{
				Vector3 get();
				void set(Vector3 value);
			}
		};

		public ref class Note : Element
		{
			ScalarArray^ _coords;
			NodePtrArray^ _nodes;

		internal:
			Note(btSoftBody::Note* native);

		public:
			property ScalarArray^ Coords
			{
				ScalarArray^ get();
			}

			property NodePtrArray^ Nodes
			{
				NodePtrArray^ get();
			}

			property Vector3 Offset
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property int Rank
			{
				int get();
				void set(int value);
			}

			property String^ Text
			{
				String^ get();
				void set(String^ value);
			}
		};

		// Not to be confused with Mogre::Pose
		public ref class Pose
		{
		internal:
			btSoftBody::Pose* _native;

		private:
			AlignedVector3Array^ _positions;

		internal:
			Pose(btSoftBody::Pose* native);

		public:
			property Matrix Aqq
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 Com
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property bool IsFrameValid
			{
				bool get();
				void set(bool value);
			}

			property bool IsVolumeValid
			{
				bool get();
				void set(bool value);
			}

			property AlignedVector3Array^ Positions
			{
				AlignedVector3Array^ get();
			}

			property Matrix Rotation
			{
				Matrix get();
				void set(Matrix value);
			}

			property Matrix Scale
			{
				Matrix get();
				void set(Matrix value);
			}

			property btScalar Volume
			{
				btScalar get();
				void set(btScalar value);
			}

			property AlignedScalarArray^ Weights
			{
				AlignedScalarArray^ get();
			}
		};
/*
		public ref class RayFromToCaster : ICollide
		{
		internal:
			RayFromToCaster(btSoftBody::RayFromToCaster* native);

		public:
			RayFromToCaster(Vector3 rayFrom, Vector3 rayTo, btScalar mxt);

			static btScalar RayFromToTriangle(Vector3 rayFrom, Vector3 rayTo, Vector3 rayNormalizedDirection,
				Vector3 a, Vector3 b, Vector3 c, btScalar maxt);
			static btScalar RayFromToTriangle(Vector3 rayFrom, Vector3 rayTo, Vector3 rayNormalizedDirection,
				Vector3 a, Vector3 b, Vector3 c);

			property Face^ Face
			{
				BulletSharp::Face^ get();
				void set(BulletSharp::Face^ value);
			}

			property btScalar Mint
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 RayFrom
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 RayNormalizedDirection
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 RayTo
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property int Tests
			{
				int get();
				void set(int value);
			}
		};
*/
		public ref class RigidContact
		{
		internal:
			btSoftBody::RContact* _native;

		private:
			BulletSharp::SoftBody::Node^ _node;

		internal:
			RigidContact(btSoftBody::RContact* native);

			/*
			~RigidContact();
			!RigidContact();
			*/
		public:
			//RigidContact();

			property Matrix C0
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 C1
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property btScalar C2
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar C3
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar C4
			{
				btScalar get();
				void set(btScalar value);
			}

			property Node^ Node
			{
				BulletSharp::SoftBody::Node^ get();
				void set(BulletSharp::SoftBody::Node^ value);
			}

			property ContactInfo^ ContactInfo
			{
				BulletSharp::SoftBody::ContactInfo^ get();
			}
		};

		public ref class SoftContact
		{
		internal:
			btSoftBody::SContact* _native;

		private:
			ScalarArray^ _cfm;
			BulletSharp::SoftBody::Face^ _face;
			BulletSharp::SoftBody::Node^ _node;

		internal:
			SoftContact(btSoftBody::SContact* native);

		public:
			property ScalarArray^ Cfm
			{
				ScalarArray^ get();
			}

			property Face^ Face
			{
				BulletSharp::SoftBody::Face^ get();
				void set(BulletSharp::SoftBody::Face^ value);
			}

			property btScalar Friction
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Margin
			{
				btScalar get();
				void set(btScalar value);
			}

			property Node^ Node
			{
				BulletSharp::SoftBody::Node^ get();
				void set(BulletSharp::SoftBody::Node^ value);
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property Vector3 Weights
			{
				Vector3 get();
				void set(Vector3 value);
			}
		};
/*
		public ref class sMedium
		{
		internal:
			btSoftBody::sMedium* _native;

			sMedium(btSoftBody::sMedium* native);

			~sMedium();
			!sMedium();

		public:
			sMedium();

			property btScalar Density
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Pressure
			{
				btScalar get();
				void set(btScalar value);
			}

			property Vector3 Velocity
			{
				Vector3 get();
				void set(Vector3 value);
			}
		};
*/
		public ref class SolverState
		{
		internal:
			btSoftBody::SolverState* _native;

			SolverState(btSoftBody::SolverState* native);

		public:
			property btScalar InverseSdt
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar RadialMargin
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar Sdt
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar UpdateMargin
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar VelocityMargin
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public ref class SRayCast
		{
		public:
			property BulletSharp::SoftBody::SoftBody^ Body;
			property EFeature Feature;
			property btScalar Fraction;
			property int Index;
		};

		public ref class Tetra : Feature
		{
			Vector3Array^ _c0;
#ifndef DISABLE_DBVT
			DbvtNode^ _leaf;
#endif
			NodePtrArray^ _nodes;

		internal:
			Tetra(btSoftBody::Tetra* native);

		public:
			property Vector3Array^ C0
			{
				Vector3Array^ get();
			}

			property btScalar C1
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar C2
			{
				btScalar get();
				void set(btScalar value);
			}
#ifndef DISABLE_DBVT
			property DbvtNode^ Leaf
			{
				DbvtNode^ get();
				void set(DbvtNode^ value);
			}
#endif

			property NodePtrArray^ Nodes
			{
				NodePtrArray^ get();
			}

			property btScalar RestVolume
			{
				btScalar get();
				void set(btScalar value);
			}
		};

		public ref class SoftBody : CollisionObject
		{
			List<AJoint::IControl^>^ _aJointControls;
			AlignedAnchorArray^ _anchors;
			Vector3Array^ _bounds;
#ifndef DISABLE_DBVT
			Dbvt^ _clusterDbvt;
#endif
			Config^ _config;
			//AlignedBoolArray^ _clusterConnectivity;
			AlignedClusterArray^ _clusters;
			AlignedCollisionObjectArray^ _collisionDisabledObjects;
			AlignedFaceArray^ _faces;
#ifndef DISABLE_DBVT
			Dbvt^ _faceDbvt;
#endif
			AlignedJointArray^ _joints;
			AlignedLinkArray^ _links;
			AlignedMaterialArray^ _materials;
#ifndef DISABLE_DBVT
			Dbvt^ _nodeDbvt;
#endif
			AlignedNodeArray^ _nodes;
			AlignedNoteArray^ _notes;
			BulletSharp::SoftBody::Pose^ _pose;
			AlignedRigidContactArray^ _rigidContacts;
			SoftBodySolver^ _softBodySolver;
			AlignedSoftContactArray^ _softContacts;
			SolverState^ _solverState;
			Object^ _tag;
			AlignedTetraArray^ _tetras;
			AlignedIntArray^ _userIndexMapping;
			SoftBodyWorldInfo^ _worldInfo;

		internal:
			SoftBody(btSoftBody* native);

			~SoftBody();
			!SoftBody();

		public:
			SoftBody(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ x, array<btScalar>^ m);
			SoftBody(SoftBodyWorldInfo^ worldInfo, Vector3Array^ x, ScalarArray^ m);
			SoftBody(SoftBodyWorldInfo^ worldInfo);

			void AddAeroForceToFace(Vector3 windVelocity, int faceIndex);
			void AddAeroForceToNode(Vector3 windVelocity, int nodeIndex);
			void AddForce(Vector3 force);
			void AddForce(Vector3 force, int node);
			void AddVelocity(Vector3 velocity, int node);
			void AddVelocity(Vector3 velocity);
			void AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies,
				btScalar influence);
			void AppendAnchor(int node, RigidBody^ body, Vector3 localPivot, bool disableCollisionBetweenLinkedBodies);
			void AppendAnchor(int node, RigidBody^ body, Vector3 localPivot);
			void AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies,
				btScalar influence);
			void AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies);
			void AppendAnchor(int node, RigidBody^ body);
			void AppendAngularJoint(AJoint::Specs^ specs, Body^ body);
			void AppendAngularJoint(AJoint::Specs^ specs);
			void AppendAngularJoint(AJoint::Specs^ specs, SoftBody^ body);
			void AppendAngularJoint(AJoint::Specs^ specs, Cluster^ body0, Body^ body1);
			void AppendFace(int model, Material^ material);
			void AppendFace(int model);
			void AppendFace();
			void AppendFace(int node0, int node1, int node2, Material^ material);
			void AppendFace(int node0, int node1, int node2);
			void AppendLinearJoint(LJoint::Specs^ specs, SoftBody^ body);
			void AppendLinearJoint(LJoint::Specs^ specs, Body^ body);
			void AppendLinearJoint(LJoint::Specs^ specs);
			void AppendLinearJoint(LJoint::Specs^ specs, Cluster^ body0, Body^ body1);
			void AppendLink(int node0, int node1, Material^ material, bool checkExist);
			void AppendLink(int node0, int node1, Material^ material);
			void AppendLink(int node0, int node1);
			void AppendLink(int model, Material^ material);
			void AppendLink(int model);
			void AppendLink();
			void AppendLink(Node^ node0, Node^ node1, Material^ material, bool checkExist);
			void AppendLink(Node^ node0, Node^ node1, Material^ material);
			void AppendLink(Node^ node0, Node^ node1);
			Material^ AppendMaterial();
			void AppendNode(Vector3 x, btScalar m);
			void AppendNote(String^ text, Vector3 o, Face^ feature);
			void AppendNote(String^ text, Vector3 o, Link^ feature);
			void AppendNote(String^ text, Vector3 o, Node^ feature);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2,
				Node^ n3);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0);
			void AppendNote(String^ text, Vector3 o, Vector4 c);
			void AppendNote(String^ text, Vector3 o);
			void AppendTetra(int model, Material^ material);
			void AppendTetra(int node0, int node1, int node2, int node3, Material^ material);
			void AppendTetra(int node0, int node1, int node2, int node3);
			void ApplyClusters(bool drift);
			void ApplyForces();
			bool CheckContact(CollisionObjectWrapper^ colObjWrap, Vector3 x, btScalar margin,
				ContactInfo^ cti);
			bool CheckFace(int node0, int node1, int node2);
			bool CheckLink(Node^ node0, Node^ node1);
			bool CheckLink(int node0, int node1);
			void CleanupClusters();
			static void ClusterAImpulse(Cluster^ cluster, Impulse^ impulse);
			Vector3 ClusterCom(int cluster);
			static Vector3 ClusterCom(Cluster^ cluster);
			static void ClusterDAImpulse(Cluster^ cluster, Vector3 impulse);
			static void ClusterDCImpulse(Cluster^ cluster, Vector3 impulse);
			static void ClusterDImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse);
			static void ClusterImpulse(Cluster^ cluster, Vector3 rpos, Impulse^ impulse);
			static void ClusterVAImpulse(Cluster^ cluster, Vector3 impulse);
			static Vector3 ClusterVelocity(Cluster^ cluster, Vector3 rpos);
			static void ClusterVImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse);
			bool CutLink(Node^ node0, Node^ node1, btScalar position);
			bool CutLink(int node0, int node1, btScalar position);
			void DampClusters();
			void DefaultCollisionHandler(CollisionObjectWrapper^ pcoWrap);
			void DefaultCollisionHandler(SoftBody^ psb);
			Vector3 EvaluateCom();
			int GenerateBendingConstraints(int distance, Material^ material);
			int GenerateBendingConstraints(int distance);
			int GenerateClusters(int k, int maxIterations);
			int GenerateClusters(int k);
			void GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
			int GetFaceVertexData([Out] array<Vector3>^% vertices); // helper
			int GetFaceVertexNormalData([Out] array<Vector3>^% data); // helper
			int GetFaceVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals); // helper
			int GetLinkVertexData([Out] array<Vector3>^% vertices); // helper
			int GetLinkVertexNormalData([Out] array<Vector3>^% data); // helper
			btScalar GetMass(int node);
			//static psolver_t GetSolver(btSoftBody::ePSolver::_ solver);
			//static vsolver_t GetSolver(btSoftBody::eVSolver::_ solver);
			int GetTetraVertexData([Out] array<Vector3>^% vertices); // helper
			int GetTetraVertexNormalData([Out] array<Vector3>^% data); // helper
			int GetTetraVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals); // helper
			int GetVertexNormalData([Out] array<Vector3>^% data); // helper
			int GetVertexNormalData([Out] array<Vector3>^% vertices, [Out] array<Vector3>^% normals); // helper
			//void IndicesToPointers(array<int>^ map);
			void IndicesToPointers();
			void InitDefaults();
			void InitializeClusters();
			void InitializeFaceTree();
			void IntegrateMotion();
			void PointersToIndices();
			void PredictMotion(btScalar deltaTime);
			void PrepareClusters(int iterations);
			static void PSolveAnchors(SoftBody^ psb, btScalar kst, btScalar ti);
			static void PSolveLinks(SoftBody^ psb, btScalar kst, btScalar ti);
			static void PSolveRContacts(SoftBody^ psb, btScalar kst, btScalar ti);
			static void PSolveSContacts(SoftBody^ psb, btScalar __unnamed1, btScalar ti);
			void RandomizeConstraints();
			bool RayTest(Vector3 rayFrom, Vector3 rayTo, SRayCast^ results);
			int RayTest(Vector3 rayFrom, Vector3 rayTo, [Out] btScalar% mint, [Out] EFeature% feature,
				[Out] int% index, bool countOnly);
			void Refine(ImplicitFn^ ifn, btScalar accurary, bool cut);
			void ReleaseCluster(int index);
			void ReleaseClusters();
			void ResetLinkRestLengths();
			void Rotate(Quaternion rotation);
			void Scale(Vector3 scale);
			void SetMass(int node, btScalar mass);
			void SetPose(bool volume, bool frame);
			void SetSolver(ESolverPresets preset);
			void SetTotalDensity(btScalar density);
			void SetTotalMass(btScalar mass, bool fromFaces);
			void SetTotalMass(btScalar mass);
			void SetVelocity(Vector3 velocity);
			void SetVolumeDensity(btScalar density);
			void SetVolumeMass(btScalar mass);
			static void SolveClusters(AlignedSoftBodyArray^ bodies);
			void SolveClusters(btScalar sor);
			static void SolveCommonConstraints(array<SoftBody^>^ bodies, int iterations);
			void SolveConstraints();
			void StaticSolve(int iterations);
			void Transform(Matrix transform);
			void Translate(Vector3 translation);
			void Translate(btScalar x, btScalar y, btScalar z); // helper
			static SoftBody^ Upcast(CollisionObject^ colObj);
			void UpdateArea(bool averageArea);
			void UpdateArea();
			void UpdateBounds();
			void UpdateClusters();
			void UpdateConstants();
			void UpdateLinkConstants();
			void UpdateNormals();
			void UpdatePose();
			static void VSolveLinks(SoftBody^ psb, btScalar kst);

		private:
			void StoreAngularJointControlRef(AJoint::Specs^ specs);

		public:
			property AlignedAnchorArray^ Anchors
			{
				AlignedAnchorArray^ get();
			}

			property Vector3Array^ Bounds
			{
				Vector3Array^ get();
			}

			property Config^ Cfg
			{
				Config^ get();
			}
			/*
			property AlignedBoolArray^ ClusterConnectivity
			{
				AlignedBoolArray^ get();
			}
			*/
			property int ClusterCount
			{
				int get();
			}
#ifndef DISABLE_DBVT
			property Dbvt^ ClusterDbvt
			{
				Dbvt^ get();
			}
#endif
			property AlignedClusterArray^ Clusters
			{
				AlignedClusterArray^ get();
			}

			property AlignedCollisionObjectArray^ CollisionDisabledObjects
			{
				AlignedCollisionObjectArray^ get();
			}

			property AlignedFaceArray^ Faces
			{
				AlignedFaceArray^ get();
			}
#ifndef DISABLE_DBVT
			property Dbvt^ FaceDbvt
			{
				Dbvt^ get();
			}
#endif
			property Matrix InitialWorldTransform
			{
				Matrix get();
				void set(Matrix value);
			}

			property AlignedJointArray^ Joints
			{
				AlignedJointArray^ get();
			}

			property AlignedLinkArray^ Links
			{
				AlignedLinkArray^ get();
			}

			property AlignedMaterialArray^ Materials
			{
				AlignedMaterialArray^ get();
			}
#ifndef DISABLE_DBVT
			property Dbvt^ NodeDbvt
			{
				Dbvt^ get();
			}
#endif
			property AlignedNodeArray^ Nodes
			{
				AlignedNodeArray^ get();
			}

			property AlignedNoteArray^ Notes
			{
				AlignedNoteArray^ get();
			}

			property Pose^ Pose
			{
				BulletSharp::SoftBody::Pose^ get();
			}

			property btScalar RestLengthScale
			{
				btScalar get();
				void set(btScalar restLength);
			}

			property AlignedRigidContactArray^ RigidContacts
			{
				AlignedRigidContactArray^ get();
			}

			property SoftBodySolver^ SoftBodySolver
			{
				BulletSharp::SoftBody::SoftBodySolver^ get();
				void set(BulletSharp::SoftBody::SoftBodySolver^ softBodySolver);
			}

			property AlignedSoftContactArray^ SoftContacts
			{
				AlignedSoftContactArray^ get();
			}

			property SolverState^ SolverState
			{
				BulletSharp::SoftBody::SolverState^ get();
			}

			property Object^ Tag
			{
				Object^ get();
				void set(Object^ value);
			}

			property AlignedTetraArray^ Tetras
			{
				AlignedTetraArray^ get();
			}

			property btScalar TimeAccumulator
			{
				btScalar get();
				void set(btScalar value);
			}

			property btScalar TotalMass
			{
				btScalar get();
				void set(btScalar value);
			}

			property bool UpdateRuntimeConstants
			{
				bool get();
				void set(bool value);
			}

			property AlignedIntArray^ UserIndexMapping
			{
				AlignedIntArray^ get();
			}

			property btScalar Volume
			{
				btScalar get();
			}

			property Vector3 WindVelocity
			{
				Vector3 get();
				void set(Vector3 velocity);
			}

			property SoftBodyWorldInfo^ WorldInfo
			{
				SoftBodyWorldInfo^ get();
				void set(SoftBodyWorldInfo^ value);
			}
		};
	};
};
