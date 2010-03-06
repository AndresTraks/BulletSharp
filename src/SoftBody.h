#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class BroadphaseInterface;
	ref class Dispatcher;
	//ref class SparseSdf;

	public ref class SoftBodyWorldInfo
	{
	public:
		SoftBodyWorldInfo();
	private:
		btSoftBodyWorldInfo* _info;
	public:
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

		//property BulletSharp::SparseSdf^ SparseSdf
		//{
		//	BulletSharp::SparseSdf^ get();
		//	void set(BulletSharp::SparseSdf^ value);
		//}

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

	public ref class SoftBody : CollisionObject
	{
	public:
		[Flags]
		enum class FCollisions
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

		ref class Config
		{
		private:
			btSoftBody::Config* _config;
		internal:
			Config(btSoftBody::Config* config);
		public:
			property FCollisions Collisions
			{
				FCollisions get();
				void set(FCollisions value);
			}

			property int PIterations
			{
				int get();
				void set(int value);
			}

			property btSoftBody::Config* UnmanagedPointer
			{
				btSoftBody::Config* get();
				void set(btSoftBody::Config* value);
			};
		};

	internal:
		SoftBody(btSoftBody* body);
	public:
		SoftBody(SoftBodyWorldInfo^ worldInfo,
			int node_count, Vector3 x, btScalar m);

		int GenerateClusters(int k, int maxIterations);
		int GenerateClusters(int k);
		void Scale(Vector3 scale);
		void SetVolumeMass(btScalar mass);
		void Translate(Vector3 translation);
		void Translate(btScalar x, btScalar y, btScalar z); // helper

		property Config^ Cfg
		{
			Config^ get();
			void set(Config^ value);
		}

	internal:
		property btSoftBody* UnmanagedPointer
		{
			btSoftBody* get() new;
		}
	};
};
