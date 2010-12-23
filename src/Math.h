#pragma once

#if GRAPHICS_NONE
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#elif GRAPHICS_AXIOM
#define Matrix Matrix4^
#elif GRAPHICS_MOGRE
#define Matrix Matrix4^
#elif GRAPHICS_OPENTK
#ifdef BT_USE_DOUBLE_PRECISION
#define Matrix Matrix4d
#else
#define Matrix Matrix4
#endif
#elif GRAPHICS_WAPICODEPACK
#define Vector3 Vector3F
#define Vector4 Vector4F
#define Quaternion Vector4
#define Matrix Matrix4x4F
#endif

#if defined(BT_USE_DOUBLE_PRECISION) && !defined(GRAPHICS_NONE) && !defined(GRAPHICS_OPENTK)
#define GRAPHICS_NO_DIRECT_CAST
#endif

namespace BulletSharp
{
	private ref class Math
	{
	public:
		static int* IntArrayToUnmanaged(array<int>^);
		static int* IntArrayToUnmanaged(array<int>^, int);

		static btScalar* BtScalarArrayToUnmanaged(array<btScalar>^);
		static btScalar* BtScalarArrayToUnmanaged(array<btScalar>^, int);

		static inline Vector3 BtVector3ToVector3(const btVector3* vector)
		{
			return Vector3(vector->m_floats[0], vector->m_floats[1], vector->m_floats[2]);
		}
		static btVector3* Vector3ToBtVector3(Vector3);
		static void Vector3ToBtVector3(Vector3, btVector3*);
		static btVector3* Vector3ArrayToUnmanaged(array<Vector3>^);
		static array<Vector3>^ Vector3ArrayToManaged(btVector3*, int);

		static inline Vector4 BtVector4ToVector4(const btVector4* vector)
		{
			return Vector4(vector->m_floats[0], vector->m_floats[1], vector->m_floats[2], vector->m_floats[3]);
		}
		static btVector4* Vector4ToBtVector4(Vector4);
		static void Vector4ToBtVector4(Vector4, btVector4*);

		static Quaternion BtQuatToQuaternion(const btQuaternion*);
		static btQuaternion* QuaternionToBtQuat(Quaternion);

		static Matrix BtTransformToMatrix(const btTransform*);
		static btTransform* MatrixToBtTransform(Matrix);
		static void MatrixToBtTransform(Matrix, btTransform*);

		static Matrix BtMatrix3x3ToMatrix(const btMatrix3x3*);
		static btMatrix3x3* MatrixToBtMatrix3x3(Matrix);
		static void MatrixToBtMatrix3x3(Matrix, btMatrix3x3*);
	};
};
