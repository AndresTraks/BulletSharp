#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class BuSimplex1To4 : PolyhedralConvexAabbCachingShape
	{
	internal:
		BuSimplex1To4(btBU_Simplex1to4* native);

	public:
		BuSimplex1To4();
		BuSimplex1To4(Vector3 pt0);
		BuSimplex1To4(Vector3 pt0, Vector3 pt1);
		BuSimplex1To4(Vector3 pt0, Vector3 pt1, Vector3 pt2);
		BuSimplex1To4(Vector3 pt0, Vector3 pt1, Vector3 pt2, Vector3 pt3);

		void AddVertexRef(Vector3% pt);
		void AddVertex(Vector3 pt);
		int GetIndex(int i);
		void Reset();
	};
};
