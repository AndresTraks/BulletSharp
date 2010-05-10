#pragma once

UsingFrameworkNamespace

#if GRAPHICS_NONE
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#elif GRAPHICS_MOGRE
#define Matrix Matrix4^
#elif GRAPHICS_OPENTK
#if BT_USE_DOUBLE_PRECISION
#define Matrix Matrix4d
#else
#define Matrix Matrix4
#endif
#elif GRAPHICS_AXIOM
#define Matrix Matrix4^
#endif

namespace BulletSharp
{
	private ref class Math
	{
	public:
		static Vector3 BtVector3ToVector3(const btVector3*);
		static btVector3* Vector3ToBtVector3(Vector3);
		static void Vector3ToBtVector3(Vector3, btVector3*);

		static Vector4 BtVector4ToVector4(const btVector4*);
		static btVector4* Vector4ToBtVector4(Vector4);
		static void Vector4ToBtVector4(Vector4, btVector4*);

		static Quaternion BtQuatToQuaternion(const btQuaternion*);
		static btQuaternion* QuaternionToBtQuat(Quaternion);

		static Matrix BtTransformToMatrix(const btTransform*);
		static btTransform* MatrixToBtTransform(Matrix);
		static void MatrixToBtTransform(Matrix, btTransform*);

		static btMatrix3x3* MatrixToBtMatrix3x3(Matrix);
	};
};
