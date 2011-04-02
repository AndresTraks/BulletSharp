#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class AlignedIntArray;
	ref class AlignedVector3Array;
	ref class FloatArray;

	public ref class Face
	{
	private:
		btFace* _face;

	public:
		Face();

		property AlignedIntArray^ ConnectedFaces
		{
			AlignedIntArray^ get();
			void set(AlignedIntArray^ value);
		}

		property AlignedIntArray^ Indices
		{
			AlignedIntArray^ get();
			void set(AlignedIntArray^ value);
		}

		property FloatArray^ Plane
		{
			FloatArray^ get();
		}

	internal:
		property btFace* UnmanagedPointer
		{
			btFace* get();
			void set(btFace* value);
		}
	};

	public ref class ConvexPolyhedron : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btConvexPolyhedron* _convexPolyhedron;

	internal:
		ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron);

	public:
		!ConvexPolyhedron();
	protected:
		~ConvexPolyhedron();

	public:
		ConvexPolyhedron();

		void Initialize();
		void Project(Matrix transform, Vector3 direction, [Out] float% min, [Out] float% max);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property Vector3 LocalCenter
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property AlignedVector3Array^ UniqueEdges
		{
			AlignedVector3Array^ get();
			void set(AlignedVector3Array^ value);
		}

		property AlignedVector3Array^ Vertices
		{
			AlignedVector3Array^ get();
			void set(AlignedVector3Array^ value);
		}

	internal:
		property btConvexPolyhedron* UnmanagedPointer
		{
			btConvexPolyhedron* get();
			void set(btConvexPolyhedron* value);
		}
	};
};
