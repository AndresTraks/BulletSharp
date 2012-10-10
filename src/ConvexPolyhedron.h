#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class AlignedIntArray;
	ref class AlignedVector3Array;
	ref class ScalarArray;

	public ref class Face
	{
	internal:
		btFace* _native;

	public:
		Face();
		
		/*
		property AlignedIntArray^ ConnectedFaces
		{
			AlignedIntArray^ get();
			void set(AlignedIntArray^ value);
		}
		*/

		property AlignedIntArray^ Indices
		{
			AlignedIntArray^ get();
		}

		property ScalarArray^ Plane
		{
			ScalarArray^ get();
		}
	};

	public ref class ConvexPolyhedron : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	internal:
		btConvexPolyhedron* _native;

		ConvexPolyhedron(btConvexPolyhedron* convexPolyhedron);

	public:
		!ConvexPolyhedron();
	protected:
		~ConvexPolyhedron();

	public:
		ConvexPolyhedron();

		void Initialize();
		void Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj, [Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax);
		bool TestContainment();

		property Vector3 C
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 E
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 Extents
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property bool IsDisposed
		{
			virtual bool get();
		}

		property Vector3 LocalCenter
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Radius
		{
			btScalar get();
			void set(btScalar value);
		}

		property AlignedVector3Array^ UniqueEdges
		{
			AlignedVector3Array^ get();
		}

		property AlignedVector3Array^ Vertices
		{
			AlignedVector3Array^ get();
		}
	};
};
