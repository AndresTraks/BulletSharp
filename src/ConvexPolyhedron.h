#pragma once

namespace BulletSharp
{
	ref class AlignedIntArray;
	ref class AlignedVector3Array;
	ref class ScalarArray;

	public ref class Face
	{
		ScalarArray^ _plane;
		AlignedIntArray^ _indices;

	internal:
		btFace* _native;

		Face(btFace* native);

		~Face();
		!Face();

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

	public ref class ConvexPolyhedron
	{
	internal:
		btConvexPolyhedron* _native;

	private:
		AlignedVector3Array^ _uniqueEdges;
		AlignedVector3Array^ _vertices;

	internal:
		ConvexPolyhedron(btConvexPolyhedron* native);

		~ConvexPolyhedron();
		!ConvexPolyhedron();

	public:
		ConvexPolyhedron();

		void Initialize();
		void ProjectRef(Matrix% transform, Vector3% direction, [Out] btScalar% minProj,
			[Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax);
		void Project(Matrix transform, Vector3 direction, [Out] btScalar% minProj,
			[Out] btScalar% maxProj, [Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax);
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
		/*
		property AlignedFaceArray^ Faces
		{
			AlignedFaceArray^ get();
			void set(AlignedFaceArray^ value);
		}
		*/
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
