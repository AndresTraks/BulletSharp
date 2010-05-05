#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class StridingMeshInterface : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btStridingMeshInterface* _stridingMesh;

	internal:
		StridingMeshInterface(btStridingMeshInterface* stridingMesh);

	public:
		!StridingMeshInterface();
	protected:
		~StridingMeshInterface();

	public:
		StridingMeshInterface^ UpcastDetect();

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
