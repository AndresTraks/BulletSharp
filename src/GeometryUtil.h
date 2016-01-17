#pragma once

namespace BulletSharp
{
	ref class AlignedVector3Array;

	public ref class GeometryUtil sealed
	{
		GeometryUtil() {}

	public:
		static bool AreVerticesBehindPlane(Vector3 planeNormal, AlignedVector3Array^ vertices,
			btScalar margin);
		static void GetPlaneEquationsFromVertices(AlignedVector3Array^ vertices, AlignedVector3Array^ planeEquationsOut);
		static void GetVerticesFromPlaneEquations(AlignedVector3Array^ planeEquations,
			AlignedVector3Array^ verticesOut);
		//static bool IsInside(AlignedVector3Array^ vertices, Vector3 planeNormal, btScalar margin);
		static bool IsPointInsidePlanes(AlignedVector3Array^ planeEquations, Vector3 point,
			btScalar margin);
	};
};
