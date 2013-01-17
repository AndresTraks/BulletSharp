#pragma once

namespace BulletSharp
{
	ref class AlignedVector3Array;

	public ref class GeometryUtil sealed
	{
	private:
		GeometryUtil() {}

	public:
		static void GetPlaneEquationsFromVertices(AlignedVector3Array^ vertices, [Out] AlignedVector3Array^% planeEquationsOut);
		static void GetVerticesFromPlaneEquations(AlignedVector3Array^ planeEquations, [Out] AlignedVector3Array^% verticesOut);
		//static bool IsInside(AlignedVector3Array^ vertices, Vector3 planeNormal, btScalar margin);
		static bool IsPointInsidePlanes(AlignedVector3Array^ planeEquations, Vector3 point, btScalar margin);
		static bool AreVerticesBehindPlane(Vector3 planeNormal, AlignedVector3Array^ vertices, btScalar margin);
	};
};
