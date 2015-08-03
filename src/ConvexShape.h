#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	public ref class ConvexShape abstract : CollisionShape
	{
	internal:
		ConvexShape(btConvexShape* native);

	public:
		void BatchedUnitVectorGetSupportingVertexWithoutMargin(array<Vector3>^ vectors, [Out] array<Vector3>^% supportVerticesOut);
		void GetAabbNonVirtual(Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void GetAabbSlow(Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		void GetPreferredPenetrationDirection(int index, [Out] Vector3% penetrationVector);
		Vector3 LocalGetSupportingVertex(Vector3 vec);
		Vector3 LocalGetSupportingVertexWithoutMargin(Vector3 vec);
		Vector3 LocalGetSupportVertexNonVirtual(Vector3 vec);
		Vector3 LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec);
		void Project(Matrix% transform, Vector3% direction, [Out] btScalar% minProj, [Out] btScalar% maxProj,
			[Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax);

		property btScalar MarginNonVirtual
		{
			btScalar get();
		}

		property int NumPreferredPenetrationDirections
		{
			int get();
		}
	};
};
