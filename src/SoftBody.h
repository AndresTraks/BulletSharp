#pragma once

#pragma managed(push, off)
#include <BulletSoftBody/btSoftBody.h>
#pragma managed(pop)

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class BroadphaseInterface;
	ref class Dispatcher;
	ref class RigidBody;
	ref class SparseSdf;

	namespace SoftBody
	{
		ref class FaceArray;
		ref class MaterialArray;
		ref class NodeArray;

		public ref class SoftBodyWorldInfo
		{
		private:
			btSoftBodyWorldInfo* _info;

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
		public enum class FCollisions
		{
			RvsMask = btSoftBody::fCollision::RVSmask,
			SdfRs = btSoftBody::fCollision::SDF_RS,
			ClRs = btSoftBody::fCollision::CL_RS,
			SvsMask = btSoftBody::fCollision::SVSmask,
			VfSs = btSoftBody::fCollision::VF_SS,
			ClSs = btSoftBody::fCollision::CL_SS,
			ClSelf = btSoftBody::fCollision::CL_SELF,
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

		public ref class Config
		{
		private:
			btSoftBody::Config* _config;
		
		internal:
			Config(btSoftBody::Config* config);
		
		public:
			property AeroModel AeroModel
			{
				BulletSharp::SoftBody::AeroModel get();
				void set(BulletSharp::SoftBody::AeroModel value);
			}

			property btScalar CHR
			{
				btScalar get();
				void set(btScalar value);
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

			property btScalar DP
			{
				btScalar get();
				void set(btScalar value);
			}

			property FCollisions Collisions
			{
				FCollisions get();
				void set(FCollisions value);
			}

			property btScalar LF
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

			property btScalar VC
			{
				btScalar get();
				void set(btScalar value);
			}

			property btSoftBody::Config* UnmanagedPointer
			{
				btSoftBody::Config* get();
				void set(btSoftBody::Config* value);
			};
		};

		public ref class Element
		{
		internal:
			btSoftBody::Element* _element;
			Element(btSoftBody::Element* element);

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

			property btSoftBody::Feature* UnmanagedPointer
			{
				btSoftBody::Feature* get() new;
			}
		};

		public ref class Link : Feature
		{
		internal:
			Link(btSoftBody::Link* link);
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

		public ref class Node : Feature
		{
		internal:
			Node(btSoftBody::Node* node);

		public:
			property Vector3 x
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

		public ref class Face : Feature
		{
		internal:
			Face(btSoftBody::Face* face);

		public:
			property array<Node^>^ n
			{
				array<Node^>^ get();
				void set(array<Node^>^ value);
			}

			property Vector3 Normal
			{
				Vector3 get();
				void set(Vector3 set);
			}

		internal:
			property btSoftBody::Face* UnmanagedPointer
			{
				btSoftBody::Face* get() new;
			}
		};

		public ref class Note : Element
		{
		internal:
			Note(btSoftBody::Note* note);
		};

		public ref class Tetra : Feature
		{
		internal:
			Tetra(btSoftBody::Tetra* tetra);
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
			void AppendLink(int node0, int node1, Material^ mat, bool bcheckexist);
			void AppendLink(int node0, int node1, Material^ mat);
			void AppendLink(int node0, int node1);
			Material^ AppendMaterial();
			int GenerateBendingConstraints(int distance, Material^ mat);
			int GenerateBendingConstraints(int distance);
			int GenerateClusters(int k, int maxIterations);
			int GenerateClusters(int k);
			void Scale(Vector3 scale);
			void SetPose(bool bvolume, bool bframe);
			void SetTotalMass(btScalar mass, bool fromFaces);
			void SetTotalMass(btScalar mass);
			void SetVolumeMass(btScalar mass);
			void StaticSolve(int iterations);
			void Transform(Matrix transform);
			void Translate(Vector3 translation);
			void Translate(btScalar x, btScalar y, btScalar z); // helper

			static SoftBody^ Upcast(CollisionObject^ colObj);

			property Config^ Cfg
			{
				Config^ get();
				void set(Config^ value);
			}

			property FaceArray^ Faces
			{
				FaceArray^ get();
				void set(FaceArray^ value);
			}

			property MaterialArray^ Materials
			{
				MaterialArray^ get();
				void set(MaterialArray^ value);
			}

			property NodeArray^ Nodes
			{
				NodeArray^ get();
				void set(NodeArray^ value);
			}

			property btScalar TotalMass
			{
				btScalar get();
				void set(btScalar value);
			}

		internal:
			property btSoftBody* UnmanagedPointer
			{
				btSoftBody* get() new;
			}
		};
	};
};
