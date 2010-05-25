#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class BU_Simplex1to4 : PolyhedralConvexAabbCachingShape
	{
	internal:
		BU_Simplex1to4(btBU_Simplex1to4* shape);

	public:
		BU_Simplex1to4();
		BU_Simplex1to4(Vector3 pt0);
		BU_Simplex1to4(Vector3 pt0, Vector3 pt1);
		BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2);
		BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2, Vector3 pt3);

		void AddVertex(Vector3 pt);
		int GetIndex(int i);
		void Reset();

	internal:
		property btBU_Simplex1to4* UnmanagedPointer
		{
			btBU_Simplex1to4* get();
		}
	};
};
