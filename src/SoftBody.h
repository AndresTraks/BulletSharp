#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class BroadphaseInterface;
	ref class AlignedCollisionObjectArray;
	ref class Dbvt;
	ref class DbvtNode;
	ref class Dispatcher;
	ref class AlignedIntArray;
	ref class RigidBody;
	ref class AlignedScalarArray;
	ref class SparseSdf;
	ref class AlignedVector3Array;
	ref class Vector3Array;

	namespace SoftBody
	{
		ref class AlignedClusterArray;
		ref class AlignedFaceArray;
		ref class AlignedLinkArray;
		ref class AlignedMaterialArray;
		ref class AlignedNodeArray;
		ref class AlignedNodePtrArray;
		ref class AlignedNoteArray;
		ref class AlignedSoftBodyArray;
		ref class AlignedTetraArray;
		ref class AlignedPSolverArray;
		ref class AlignedVSolverArray;
		ref class Cluster;
		ref class Feature;
		ref class Impulse;
		ref class Material;
		ref class Node;
		ref class NodePtrArray;
		ref class SoftBody;

		public ref class SoftBodyWorldInfo
		{
		private:
			btSoftBodyWorldInfo* _info;

		internal:
			SoftBodyWorldInfo(btSoftBodyWorldInfo* info);

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

			property BulletSharp::SparseSdf^ SparseSdf
			{
				BulletSharp::SparseSdf^ get();
				void set(BulletSharp::SparseSdf^ value);
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

		internal:
			property btSoftBodyWorldInfo* UnmanagedPointer
			{
				btSoftBodyWorldInfo* get();
				void set(btSoftBodyWorldInfo* value);
			};
		};

		public enum class AeroModel
		{
			VPoint = btSoftBody::eAeroModel::V_Point,
			VTwoSided = btSoftBody::eAeroModel::V_TwoSided,
			VOneSided = btSoftBody::eAeroModel::V_OneSided,
			FTwoSided = btSoftBody::eAeroModel::F_TwoSided,
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

		public ref class Body
		{
		private:
			btSoftBody::Body* _body;

		public:
			Body();
			Body(Cluster^ p);
			Body(CollisionObject^ colObj);

			void Activate();
			void ApplyDImpulse(Vector3 impulse, Vector3 rPos);
			void ApplyImpulse(Impulse^ impulse, Vector3 rPos);
			void ApplyVAImpulse(Vector3 impulse);
			void ApplyDAImpulse(Vector3 impulse);
			void ApplyAImpulse(Impulse^ impulse);
			void ApplyDCImpulse(Vector3 impulse);
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

		internal:
			property btSoftBody::Body* UnmanagedPointer
			{
				btSoftBody::Body* get();
				void set(btSoftBody::Body* value);
			};
		};

		[DebuggerDisplay("ClusterIndex = {ClusterIndex}")]
		public ref class Cluster
		{
		private:
			btSoftBody::Cluster* _cluster;

		internal:
			Cluster(btSoftBody::Cluster* cluster);

		public:
			Cluster();

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
				void set(AlignedVector3Array^ value);
			}

			property Matrix FrameXForm
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
				void set(AlignedScalarArray^ value);
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
				void set(AlignedNodePtrArray^ value);
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

		internal:
			property btSoftBody::Cluster* UnmanagedPointer
			{
				btSoftBody::Cluster* get();
				void set(btSoftBody::Cluster* value);
			};
		};

		public ref class Config
		{
		private:
			btSoftBody::Config* _config;

		internal:
			Config(btSoftBody::Config* config);

		public:
			Config();

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

			property int VIterations
			{
				int get();
				void set(int value);
			}

			property btScalar VCF
			{
				btScalar get();
				void set(btScalar value);
			}

			property AlignedVSolverArray^ VSequence
			{
				AlignedVSolverArray^ get();
			}

		internal:
			property btSoftBody::Config* UnmanagedPointer
			{
				btSoftBody::Config* get();
				void set(btSoftBody::Config* value);
			};
		};

		public ref class Element
		{
		private:
			btSoftBody::Element* _element;

		internal:
			Element(btSoftBody::Element* element);

		public:
			Element();

			property Object^ Tag
			{
				Object^ get();
				void set(Object^ value);
			}

		internal:
			property btSoftBody::Element* UnmanagedPointer
			{
				btSoftBody::Element* get();
				void set(btSoftBody::Element* value);
			};
		};

		public ref class Feature : Element
		{
		internal:
			Feature(btSoftBody::Feature* feature);

		public:
			Feature();

			property BulletSharp::SoftBody::Material^ Material
			{
				BulletSharp::SoftBody::Material^ get();
				void set(BulletSharp::SoftBody::Material^ value);
			}

		internal:
			property btSoftBody::Feature* UnmanagedPointer
			{
				btSoftBody::Feature* get() new;
			}
		};

		public ref class Face : Feature
		{
		internal:
			Face(btSoftBody::Face* face);

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
				void set(Vector3 set);
			}

			property btScalar RestArea
			{
				btScalar get();
				void set(btScalar value);
			}

		internal:
			property btSoftBody::Face* UnmanagedPointer
			{
				btSoftBody::Face* get() new;
			}
		};

		public ref class Impulse
		{
		private:
			btSoftBody::Impulse* _impulse;

		internal:
			Impulse(btSoftBody::Impulse* impulse);

		public:
			Impulse();

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

			static Impulse^ operator-(Impulse^ i);
			static Impulse^ operator*(Impulse^ i, btScalar x);

		internal:
			property btSoftBody::Impulse* UnmanagedPointer
			{
				btSoftBody::Impulse* get();
				void set(btSoftBody::Impulse* value);
			};
		};

		public ref class Joint
		{
		public:
			ref class Specs
			{
			private:
				btSoftBody::Joint::Specs* _specs;

			internal:
				property btSoftBody::Joint::Specs* UnmanagedPointer
				{
					btSoftBody::Joint::Specs* get();
					void set(btSoftBody::Joint::Specs* value);
				};
			};

		private:
			btSoftBody::Joint* _joint;
		};

		public ref class LJoint : Joint
		{
		public:
			ref class Specs : Joint::Specs
			{
			public:
				Specs();

			internal:
				property btSoftBody::LJoint::Specs* UnmanagedPointer
				{
					btSoftBody::LJoint::Specs* get() new;
				};
			};
		};

		public ref class AJoint : Joint
		{
		public:
			ref class Specs : Joint::Specs
			{
			public:
				Specs();

			internal:
				property btSoftBody::AJoint::Specs* UnmanagedPointer
				{
					btSoftBody::AJoint::Specs* get() new;
				};
			};
		};

		public ref class Link : Feature
		{
		internal:
			Link(btSoftBody::Link* link);

		public:
			Link();

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

		internal:
			property btSoftBody::Link* UnmanagedPointer
			{
				btSoftBody::Link* get() new;
			}
		};

		public ref class Material : Element
		{
		internal:
			Material(btSoftBody::Material* material);

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

		internal:
			property btSoftBody::Material* UnmanagedPointer
			{
				btSoftBody::Material* get() new;
			}
		};

		[DebuggerDisplay("{X}")]
		public ref class Node : Feature
		{
		internal:
			Node(btSoftBody::Node* node);

		public:
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

		internal:
			property btSoftBody::Node* UnmanagedPointer
			{
				btSoftBody::Node* get() new;
			}
		};

		public ref class Note : Element
		{
		internal:
			Note(btSoftBody::Note* note);

		public:
			Note();

		internal:
			property btSoftBody::Note* UnmanagedPointer
			{
				btSoftBody::Note* get() new;
			}
		};

		public ref class Pose
		{
		private:
			btSoftBody::Pose* _pose;

		internal:
			Pose(btSoftBody::Pose* pose);

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
				void set(AlignedVector3Array^ value);
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
				void set(AlignedScalarArray^ value);
			}

		internal:
			property btSoftBody::Pose* UnmanagedPointer
			{
				btSoftBody::Pose* get();
				void set(btSoftBody::Pose* value);
			};
		};

		public ref class SolverState
		{
		private:
			btSoftBody::SolverState* _solverState;

		internal:
			SolverState(btSoftBody::SolverState* solverState);

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

		internal:
			property btSoftBody::SolverState* UnmanagedPointer
			{
				btSoftBody::SolverState* get();
				void set(btSoftBody::SolverState* value);
			};
		};

		public ref class SRayCast
		{
		private:
			btSoftBody::sRayCast* _rayCast;

		internal:
			SRayCast(btSoftBody::sRayCast* rayCast);

		public:
			SRayCast();

			property BulletSharp::SoftBody::SoftBody^ Body
			{
				SoftBody^ get();
				void set(SoftBody^ value);
			}

			property EFeature Feature
			{
				EFeature get();
				void set(EFeature value);
			}

			property btScalar Fraction
			{
				btScalar get();
				void set(btScalar value);
			}

			property int Index
			{
				int get();
				void set(int value);
			}

		internal:
			property btSoftBody::sRayCast* UnmanagedPointer
			{
				btSoftBody::sRayCast* get();
			}
		};

		public ref class Tetra : Feature
		{
		internal:
			Tetra(btSoftBody::Tetra* tetra);

		public:
			Tetra();

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

		internal:
			property btSoftBody::Tetra* UnmanagedPointer
			{
				btSoftBody::Tetra* get() new;
			}
		};

		public ref class SoftBody : CollisionObject
		{
		internal:
			SoftBody(btSoftBody* body);

		public:
			SoftBody(SoftBodyWorldInfo^ worldInfo, array<Vector3>^ x, array<btScalar>^ m);

			void AddForce(Vector3 force, int node);
			void AddForce(Vector3 force);
			void AddVelocity(Vector3 velocity, int node);
			void AddVelocity(Vector3 velocity);
			void AppendAnchor(int node, RigidBody^ body, bool disableCollisionBetweenLinkedBodies);
			void AppendAnchor(int node, RigidBody^ body);
			void AppendFace(int node0, int node1, int node2, Material^ material);
			void AppendFace(int node0, int node1, int node2);
			void AppendFace(int model, Material^ material);
			void AppendFace(int model);
			void AppendFace();
			void AppendLinearJoint(LJoint::Specs^ specs, Cluster^ body0, Body^ body1);
			void AppendLinearJoint(LJoint::Specs^ specs, Body^ body1);
			void AppendLinearJoint(LJoint::Specs^ specs, SoftBody^ body1);
			void AppendAngularJoint(AJoint::Specs^ specs, Cluster^ body0, Body^ body1);
			void AppendAngularJoint(AJoint::Specs^ specs, Body^ body1);
			void AppendAngularJoint(AJoint::Specs^ specs, SoftBody^ body1);
			void AppendLink(int node0, int node1, Material^ material, bool bCheckExist);
			void AppendLink(int node0, int node1, Material^ material);
			void AppendLink(int node0, int node1);
			void AppendLink(Node^ node0, Node^ node1, Material^ material, bool bCheckExist);
			void AppendLink(Node^ node0, Node^ node1, Material^ material);
			void AppendLink(Node^ node0, Node^ node1);
			void AppendLink(int model, Material^ material);
			void AppendLink(int model);
			void AppendLink();
			Material^ AppendMaterial();
			void AppendNode(Vector3 x, btScalar m);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2, Node^ n3);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1, Node^ n2);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0, Node^ n1);
			void AppendNote(String^ text, Vector3 o, Vector4 c, Node^ n0);
			void AppendNote(String^ text, Vector3 o, Vector4 c);
			void AppendNote(String^ text, Vector3 o);
			void AppendNote(String^ text, Vector3 o, Node^ feature);
			void AppendNote(String^ text, Vector3 o, Link^ feature);
			void AppendNote(String^ text, Vector3 o, Face^ feature);
			void AppendTetra(int model, Material^ material);
			void AppendTetra(int node0, int node1, int node2, int node3, Material^ material);
			void AppendTetra(int node0, int node1, int node2, int node3);
			bool CheckFace(int node0, int node1, int node2);
			bool CheckLink(int node0, int node1);
			bool CheckLink(Node^ node0, Node^ node1);
			static Vector3 ClusterCom(Cluster^ cluster);
			Vector3 ClusterCom(int cluster);
			static Vector3 ClusterVelocity(Cluster^ cluster, Vector3 rpos);
			static void ClusterVImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse);
			static void ClusterDImpulse(Cluster^ cluster, Vector3 rpos, Vector3 impulse);
			static void ClusterImpulse(Cluster^ cluster, Vector3 rpos, Impulse^ impulse);
			static void ClusterVAImpulse(Cluster^ cluster, Vector3 impulse);
			static void ClusterDAImpulse(Cluster^ cluster, Vector3 impulse);
			static void ClusterAImpulse(Cluster^ cluster, Impulse^ impulse);
			static void ClusterDCImpulse(Cluster^ cluster, Vector3 impulse);
			bool CutLink(int node0, int node1, btScalar position);
			bool CutLink(Node^ node0, Node^ node1, btScalar position);
			void DefaultCollisionHandler(CollisionObject^ pco);
			void DefaultCollisionHandler(SoftBody^ psb);
			int GenerateBendingConstraints(int distance, Material^ material);
			int GenerateBendingConstraints(int distance);
			int GenerateClusters(int k, int maxIterations);
			int GenerateClusters(int k);
			void GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
			btScalar GetMass(int node);
			void IntegrateMotion();
			void PredictMotion(btScalar dt);
			void RandomizeConstraints();
			bool RayTest(Vector3 rayFrom, Vector3 rayTo, SRayCast^ results);
			//void Refine(ImplicitFn^ ifn, btScalar accurary, bool cut);
			void ReleaseCluster(int index);
			void ReleaseClusters();
			void Rotate(Quaternion rotation);
			void Scale(Vector3 scale);
			void SetMass(int node, btScalar mass);
			void SetPose(bool bVolume, bool bFrame);
			void SetSolver(ESolverPresets preset);
			void SetTotalDensity(btScalar density);
			void SetTotalMass(btScalar mass, bool fromFaces);
			void SetTotalMass(btScalar mass);
			void SetVelocity(Vector3 velocity);
			void SetVolumeDensity(btScalar density);
			void SetVolumeMass(btScalar mass);
			static void SolveClusters(AlignedSoftBodyArray^ bodies);
			static void SolveCommonConstraints(array<SoftBody^>^ bodies, int iterations);
			void SolveConstraints();
			void StaticSolve(int iterations);
			void Transform(Matrix transform);
			void Translate(Vector3 translation);
			void Translate(btScalar x, btScalar y, btScalar z); // helper

			static SoftBody^ Upcast(CollisionObject^ colObj);

			property Vector3Array^ Bounds
			{
				Vector3Array^ get();
			}

			property AlignedClusterArray^ Clusters
			{
				AlignedClusterArray^ get();
				void set(AlignedClusterArray^ value);
			}

			property Config^ Cfg
			{
				Config^ get();
				void set(Config^ value);
			}

			property int ClusterCount
			{
				int get();
			}

			property AlignedCollisionObjectArray^ CollisionDisabledObjects
			{
				AlignedCollisionObjectArray^ get();
				void set(AlignedCollisionObjectArray^ value);
			}

			property AlignedFaceArray^ Faces
			{
				AlignedFaceArray^ get();
				void set(AlignedFaceArray^ value);
			}

			property Matrix InitialWorldTransform
			{
				Matrix get();
				void set(Matrix value);
			}

			property AlignedLinkArray^ Links
			{
				AlignedLinkArray^ get();
				void set(AlignedLinkArray^ value);
			}

			property AlignedMaterialArray^ Materials
			{
				AlignedMaterialArray^ get();
				void set(AlignedMaterialArray^ value);
			}

			property AlignedNodeArray^ Nodes
			{
				AlignedNodeArray^ get();
				void set(AlignedNodeArray^ value);
			}

			property AlignedNoteArray^ Notes
			{
				AlignedNoteArray^ get();
				void set(AlignedNoteArray^ value);
			}

			property Pose^ Pose
			{
				BulletSharp::SoftBody::Pose^ get();
				void set(BulletSharp::SoftBody::Pose^ value);
			}

			property SolverState^ SolverState
			{
				BulletSharp::SoftBody::SolverState^ get();
				void set(BulletSharp::SoftBody::SolverState^ value);
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
				void set(AlignedIntArray^ value);
			}

			property btScalar Volume
			{
				btScalar get();
			}

			property Vector3 WindVelocity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			property SoftBodyWorldInfo^ WorldInfo
			{
				SoftBodyWorldInfo^ get();
				void set(SoftBodyWorldInfo^ value);
			}

#ifndef DISABLE_DBVT
			property Dbvt^ ClusterDbvt
			{
				Dbvt^ get();
				void set(Dbvt^ value);
			}

			property Dbvt^ FaceDbvt
			{
				Dbvt^ get();
				void set(Dbvt^ value);
			}

			property Dbvt^ NodeDbvt
			{
				Dbvt^ get();
				void set(Dbvt^ value);
			}
#endif

		internal:
			property btSoftBody* UnmanagedPointer
			{
				btSoftBody* get() new;
			}
		};
	};
};
