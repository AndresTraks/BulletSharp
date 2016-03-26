#pragma once

#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ScalarArray;
	ref class Vector3Array;

	public ref class SubSimplexClosestResult
	{
	internal:
		btSubSimplexClosestResult* _native;

	private:
		ScalarArray^ _barycentricCoords;

	internal:
		SubSimplexClosestResult(btSubSimplexClosestResult* native);

		~SubSimplexClosestResult();
		!SubSimplexClosestResult();

	public:
		SubSimplexClosestResult();

		void Reset();
		void SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c, btScalar d);
		void SetBarycentricCoordinates(btScalar a, btScalar b, btScalar c);
		void SetBarycentricCoordinates(btScalar a, btScalar b);
		void SetBarycentricCoordinates(btScalar a);
		void SetBarycentricCoordinates();

		property ScalarArray^ BarycentricCoords
		{
			ScalarArray^ get();
		}

		property Vector3 ClosestPointOnSimplex
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property bool Degenerate
		{
			bool get();
			void set(bool value);
		}

		property bool IsValid
		{
			bool get();
		}
		/*
		property UsageBitfield^ UsedVertices
		{
			UsageBitfield^ get();
			void set(UsageBitfield^ value);
		}
		*/
	};

#ifdef NO_VIRTUAL_INTERFACE
	public ref class VoronoiSimplexSolver
#else
	public ref class VoronoiSimplexSolver : SimplexSolverInterface
#endif
	{
	internal:
#ifdef NO_VIRTUAL_INTERFACE
		btVoronoiSimplexSolver* _native;
		VoronoiSimplexSolver(btVoronoiSimplexSolver* native, bool preventDelete);
#else
		VoronoiSimplexSolver(btVoronoiSimplexSolver* native);
#endif

#ifdef NO_VIRTUAL_INTERFACE
	private:
		bool _preventDelete;

		~VoronoiSimplexSolver();
		!VoronoiSimplexSolver();
#endif

	public:
		VoronoiSimplexSolver();

		void AddVertex(Vector3 w, Vector3 p, Vector3 q);
		void BackupClosest(Vector3 v);
		bool Closest(Vector3 v);
		bool ClosestPtPointTetrahedron(Vector3 p, Vector3 a, Vector3 b, Vector3 c,
			Vector3 d, SubSimplexClosestResult^ finalResult);
		bool ClosestPtPointTriangle(Vector3 p, Vector3 a, Vector3 b, Vector3 c, SubSimplexClosestResult^ result);
		void ComputePoints(Vector3 p1, Vector3 p2);
		bool EmptySimplex();
		bool FullSimplex();
		int GetSimplex([Out] array<Vector3>^% pBuf, [Out] array<Vector3>^% qBuf, [Out] array<Vector3>^% yBuf);
		bool InSimplex(Vector3 w);
		btScalar MaxVertex();
		int PointOutsideOfPlane(Vector3 p, Vector3 a, Vector3 b, Vector3 c, Vector3 d);
		//void ReduceVertices(UsageBitfield^ usedVerts);
		void RemoveVertex(int index);
		void Reset();
		bool UpdateClosestVectorAndPoints();

		property SubSimplexClosestResult^ CachedBC
		{
			SubSimplexClosestResult^ get();
		}

		property Vector3 CachedP1
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 CachedP2
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 CachedV
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property bool CachedValidClosest
		{
			bool get();
			void set(bool value);
		}

		property btScalar EqualVertexThreshold
		{
			btScalar get();
			void set(btScalar threshold);
		}

		property Vector3 LastW
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property bool NeedsUpdate
		{
			bool get();
			void set(bool value);
		}

		property int NumVertices
		{
			int get();
			void set(int value);
		}

		property Vector3Array^ SimplexPointsP
		{
			Vector3Array^ get();
		}

		property Vector3Array^ SimplexPointsQ
		{
			Vector3Array^ get();
		}

		property Vector3Array^ SimplexVectorW
		{
			Vector3Array^ get();
		}
	};
};
