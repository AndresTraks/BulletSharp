#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class StridingMeshInterface abstract : BulletSharp::IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btStridingMeshInterface* _stridingMesh;

		protected:
			StridingMeshInterface(btStridingMeshInterface* stridingMesh);

		public:
			!StridingMeshInterface();
		protected:
			~StridingMeshInterface();

		public:
			property bool IsDisposed
			{
				virtual bool get();
			}

		public:
			void StridingMeshInterface::CalculateAabbBruteForce([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);

		internal:
			property btStridingMeshInterface* UnmanagedPointer
			{
				btStridingMeshInterface* get();
			}
	};
};
