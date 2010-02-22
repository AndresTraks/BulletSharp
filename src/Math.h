#pragma once

UsingFrameworkNamespace

namespace BulletSharp
{
	private ref class Math
	{
		internal:
			static Vector3 BtVec3ToVector3(const btVector3*);
			static btVector3* Vector3ToBtVec3(Vector3);

			static Quaternion BtQuatToQuaternion(const btQuaternion*);
			static btQuaternion* QuaternionToBtQuat(Quaternion);

			static Matrix BtTransformToMatrix(const btTransform*);
			static btTransform* MatrixToBtTransform(Matrix);
	};
};
