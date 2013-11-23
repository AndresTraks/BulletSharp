#pragma once

#if GRAPHICS_GENERIC
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#elif GRAPHICS_AXIOM
#define Matrix Matrix4^
#elif GRAPHICS_MOGRE
#define Matrix Matrix4^
using namespace Mogre;
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

#if (defined(BT_USE_DOUBLE_PRECISION) && !defined(GRAPHICS_GENERIC) && !defined(GRAPHICS_OPENTK)) || \
	(defined(BT_USE_SSE) )//&& defined (BT_USE_SIMD_VECTOR3) defined (BT_USE_SSE_IN_API))
#define GRAPHICS_NO_DIRECT_CAST
#endif

// Macros for passing Vector3 parameters.
// VECTOR3_DEF and VECTOR3_PTR convert Vector3 to btVector3, but allow pinned pointers to be passed
// if the structure of Vector3 and btVector3 is compatible.
// VECTOR3_DEL cleans up the btVector3 if pinning is not possible.
// VECTOR3_USE is used to dereference the btVector3* pointer.
// FIXME: is it safe to cast Vector3 to btVector3 given that btVector3 has padding?
#define VECTOR3_NAME(vec) vec ## Temp
#ifdef GRAPHICS_NO_DIRECT_CAST
#define VECTOR3_DEF(vec) btVector3* VECTOR3_NAME(vec) = Math::Vector3ToBtVector3(vec)
#define VECTOR3_PTR(vec) VECTOR3_NAME(vec)
#define VECTOR3_DEL(vec) ALIGNED_FREE(VECTOR3_PTR(vec))
#else
#define VECTOR3_PTR(vec) ((btVector3*) VECTOR3_NAME(vec))
#ifdef BT_USE_SSE_IN_API
#define VECTOR3_DEF(vec) btVector3* VECTOR3_NAME(vec) = Math::Vector3ToBtVector3(vec)
#define VECTOR3_DEL(vec) ALIGNED_FREE(VECTOR3_PTR(vec))
#else
#define VECTOR3_DEF(vec) pin_ptr<Vector3> VECTOR3_NAME(vec) = &vec;
#define VECTOR3_DEL(vec)
#endif
#endif
#define VECTOR3_USE(vec) *VECTOR3_PTR(vec)

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
		static inline void BtVector3ToVector3(const btVector3* vector, [Out] Vector3% vectorOut)
		{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
			vectorOut.x = vector->m_floats[0];
			vectorOut.y = vector->m_floats[1];
			vectorOut.z = vector->m_floats[2];
#else
			vectorOut.X = vector->m_floats[0];
			vectorOut.Y = vector->m_floats[1];
			vectorOut.Z = vector->m_floats[2];
#endif
		}
		static btVector3* Vector3ToBtVector3(Vector3);
		static btVector3* Vector3ToBtVector3Ref(Vector3%);
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
		static void QuaternionToBt(Quaternion, btQuaternion*);

		static Matrix BtTransformToMatrix(const btTransform*);
		static void BtTransformToMatrix(const btTransform*, [Out] Matrix%);
		static btTransform* MatrixToBtTransform(Matrix);
		static void MatrixToBtTransform(Matrix, btTransform*);

		static Matrix BtMatrix3x3ToMatrix(const btMatrix3x3*);
		static btMatrix3x3* MatrixToBtMatrix3x3(Matrix);
		static void MatrixToBtMatrix3x3(Matrix, btMatrix3x3*);
	};
};

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
#define BtVector3ToVector3Fast(v, out) \
	out.x = (v)->m_floats[0]; \
	out.y = (v)->m_floats[1]; \
	out.z = (v)->m_floats[2];
#else
#define BtVector3ToVector3Fast(v, out) \
	out.X = (v)->m_floats[0]; \
	out.Y = (v)->m_floats[1]; \
	out.Z = (v)->m_floats[2];
#endif

#define BtVector3ToVector3FastRet(v) Vector3((v)->m_floats[0], (v)->m_floats[1], (v)->m_floats[2])

#if defined(GRAPHICS_MOGRE)
#define BtTransformToMatrixFast(transform, out)	out = gcnew Mogre::Matrix4(); \
	btScalar* m = (btScalar*)&transform; \
	out->m00 = m[0]; \
	out->m01 = m[1]; \
	out->m02 = m[2]; \
	out->m30 = 0; \
	out->m10 = m[4]; \
	out->m11 = m[5]; \
	out->m12 = m[6]; \
	out->m31 = 0; \
	out->m20 = m[8]; \
	out->m21 = m[9]; \
	out->m22 = m[10]; \
	out->m32 = 0; \
	out->m03 = m[12]; \
	out->m13 = m[13]; \
	out->m23 = m[14]; \
	out->m33 = 1;
#elif defined(GRAPHICS_AXIOM)
#define BtTransformToMatrixFast(transform, out)	out = gcnew Axiom::Math::Matrix4(); \
	btScalar* m = (btScalar*)&transform; \
	out->m00 = m[0]; \
	out->m01 = m[1]; \
	out->m02 = m[2]; \
	out->m30 = 0; \
	out->m10 = m[4]; \
	out->m11 = m[5]; \
	out->m12 = m[6]; \
	out->m31 = 0; \
	out->m20 = m[8]; \
	out->m21 = m[9]; \
	out->m22 = m[10]; \
	out->m32 = 0; \
	out->m03 = m[12]; \
	out->m13 = m[13]; \
	out->m23 = m[14]; \
	out->m33 = 1;
#else
#ifdef GRAPHICS_NO_DIRECT_CAST
#define BtTransformToMatrixFast(transform, out) \
	btScalar* m = (btScalar*)&transform; \
	out.M11 = (float)m[0]; \
	out.M12 = (float)m[4]; \
	out.M13 = (float)m[8]; \
	out.M21 = (float)m[1]; \
	out.M22 = (float)m[5]; \
	out.M23 = (float)m[9]; \
	out.M31 = (float)m[2]; \
	out.M32 = (float)m[6]; \
	out.M33 = (float)m[10]; \
	out.M41 = (float)m[12]; \
	out.M42 = (float)m[13]; \
	out.M43 = (float)m[14]; \
	out.M44 = 1;
#else
#define BtTransformToMatrixFast(transform, out) pin_ptr<Matrix> ptr = &out; \
	transform.getOpenGLMatrix((btScalar*)ptr);
#endif
#endif

#ifdef GRAPHICS_AXIOM
#define Vector3_Cross(left, right, result) result = left.Cross(right)
#define Matrix_Identity Matrix4::Identity
#elif defined(GRAPHICS_MOGRE)
#define Vector3_Cross(left, right, result) result = left.CrossProduct(right)
#define Matrix_Identity Matrix4::IDENTITY
#elif defined(GRAPHICS_WAPICODEPACK)
#define Vector3_Cross(left, right, result) result = Vector3::Cross(left, right)
#define Matrix_Identity Matrix::Identity
#else
#define Vector3_Cross(left, right, result) Vector3::Cross(left, right, result)
#define Matrix_Identity Matrix::Identity
#endif
