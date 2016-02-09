#pragma once

#if GRAPHICS_MOGRE
#define Matrix Matrix4^
using namespace Mogre;
#elif GRAPHICS_NUMERICS
#define Matrix Matrix4x4
#elif GRAPHICS_OPENTK
#ifdef BT_USE_DOUBLE_PRECISION
#define Vector3 Vector3d
#define Vector4 Vector4d
#define Matrix Matrix4d
#else
#define Matrix Matrix4
#endif
#elif GRAPHICS_SHARPDX
#define Matrix SharpDX::Matrix
#define Quaternion SharpDX::Quaternion
#define Vector3 SharpDX::Vector3
#define Vector4 SharpDX::Vector4
#elif GRAPHICS_GENERIC
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#endif

#if (defined(BT_USE_DOUBLE_PRECISION) && !defined(GRAPHICS_GENERIC) && !defined(GRAPHICS_OPENTK)) || \
	(defined(BT_USE_SSE) )//&& defined (BT_USE_SIMD_VECTOR3) defined (BT_USE_SSE_IN_API))
#define GRAPHICS_NO_DIRECT_CAST
#endif

// Macros for passing Vector3 parameters.
// VECTOR3_CONV and VECTOR3_PTR convert Vector3 to btVector3, but allow pinned pointers to be passed
// if the structure of Vector3 and btVector3 is compatible.
// VECTOR3_DEL cleans up the btVector3 if pinning is not possible.
// VECTOR3_USE is used to dereference the btVector3* pointer.
// FIXME: is it safe to cast Vector3 to btVector3 given that btVector3 has padding?
#define VECTOR3_NAME(vec) vec ## Temp
#define VECTOR4_NAME(vec) vec ## Temp
#ifdef GRAPHICS_NO_DIRECT_CAST
#define VECTOR3_CONV(vec) btVector3* VECTOR3_NAME(vec) = Math::Vector3ToBtVector3(vec)
#define VECTOR3_PTR(vec) VECTOR3_NAME(vec)
#define VECTOR3_DEL(vec) ALIGNED_FREE(VECTOR3_PTR(vec))
#define VECTOR4_CONV(vec) btVector4* VECTOR4_NAME(vec) = Math::Vector4ToBtVector4(vec)
#define VECTOR4_PTR(vec) VECTOR4_NAME(vec)
#define VECTOR4_DEL(vec) ALIGNED_FREE(VECTOR4_PTR(vec))
#else
#define VECTOR3_PTR(vec) ((btVector3*) VECTOR3_NAME(vec))
#define VECTOR4_PTR(vec) ((btVector4*) VECTOR3_NAME(vec))
#ifdef BT_USE_SSE_IN_API
#define VECTOR3_CONV(vec) btVector3* VECTOR3_NAME(vec) = Math::Vector3ToBtVector3(vec)
#define VECTOR3_DEL(vec) ALIGNED_FREE(VECTOR3_PTR(vec))
#define VECTOR4_CONV(vec) btVector4* VECTOR4_NAME(vec) = Math::Vector4ToBtVector4(vec)
#define VECTOR4_DEL(vec) ALIGNED_FREE(VECTOR4_PTR(vec))
#else
#define VECTOR3_CONV(vec) pin_ptr<Vector3> VECTOR3_NAME(vec) = &vec
#define VECTOR3_DEL(vec)
#define VECTOR4_CONV(vec) pin_ptr<Vector4> VECTOR4_NAME(vec) = &vec
#define VECTOR4_DEL(vec)
#endif
#endif
#define VECTOR3_USE(vec) *VECTOR3_PTR(vec)
#define VECTOR4_USE(vec) *VECTOR4_PTR(vec)

#define TRANSFORM_NAME(t) t ## Temp
#define TRANSFORM_DEF(t) btTransform* TRANSFORM_NAME(t)
#define TRANSFORM_CONV(t) TRANSFORM_DEF(t) = Math::MatrixToBtTransform(t)
#define TRANSFORM_PTR(t) TRANSFORM_NAME(t)
#define TRANSFORM_USE(t) *TRANSFORM_PTR(t)
#define TRANSFORM_DEL(t) ALIGNED_FREE(TRANSFORM_PTR(t))

#define MATRIX3X3_NAME(t) t ## Temp
#define MATRIX3X3_DEF(t) btMatrix3x3* MATRIX3X3_NAME(t)
#define MATRIX3X3_CONV(t) MATRIX3X3_DEF(t) = Math::MatrixToBtMatrix3x3(t)
#define MATRIX3X3_PTR(t) MATRIX3X3_NAME(t)
#define MATRIX3X3_USE(t) *MATRIX3X3_PTR(t)
#define MATRIX3X3_DEL(t) ALIGNED_FREE(MATRIX3X3_PTR(t))

#define QUATERNION_NAME(t) t ## Temp
#define QUATERNION_DEF(t) btQuaternion* QUATERNION_NAME(t)
#define QUATERNION_CONV(t) QUATERNION_DEF(t) = Math::QuaternionToBtQuat(t)
#define QUATERNION_PTR(t) QUATERNION_NAME(t)
#define QUATERNION_USE(t) *QUATERNION_PTR(t)
#define QUATERNION_DEL(t) ALIGNED_FREE(QUATERNION_PTR(t))

#ifdef GRAPHICS_MOGRE
#define Vector_X(v) btScalar((v).x)
#define Vector_Y(v) btScalar((v).y)
#define Vector_Z(v) btScalar((v).z)
#define Vector_W(v) btScalar((v).w)
#define Vector_SetX(v, s) (v).x = s
#define Vector_SetY(v, s) (v).y = s
#define Vector_SetZ(v, s) (v).z = s
#define Vector_SetW(v, s) (v).w = s
#else
#define Vector_X(v) btScalar((v).X)
#define Vector_Y(v) btScalar((v).Y)
#define Vector_Z(v) btScalar((v).Z)
#define Vector_W(v) btScalar((v).W)
#define Vector_SetX(v, s) (v).X = s
#define Vector_SetY(v, s) (v).Y = s
#define Vector_SetZ(v, s) (v).Z = s
#define Vector_SetW(v, s) (v).W = s
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
		static inline void BtVector3ToVector3(const btVector3* vector, [Out] Vector3% vectorOut)
		{
			Vector_SetX(vectorOut, vector->m_floats[0]);
			Vector_SetY(vectorOut, vector->m_floats[1]);
			Vector_SetZ(vectorOut, vector->m_floats[2]);
		}
		static btVector3* Vector3ToBtVector3(Vector3%);
		static void Vector3ToBtVector3(Vector3%, btVector3*);
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
		static void QuaternionToBtQuat(Quaternion, btQuaternion*);

		static Matrix BtTransformToMatrix(const btTransform*);
		static void BtTransformToMatrix(const btTransform*, [Out] Matrix%);
		static btTransform* MatrixToBtTransform(Matrix);
		static void MatrixToBtTransform(Matrix, btTransform*);

		static Matrix BtMatrix3x3ToMatrix(const btMatrix3x3*);
		static btMatrix3x3* MatrixToBtMatrix3x3(Matrix);
		static void MatrixToBtMatrix3x3(Matrix, btMatrix3x3*);
	};
};

#define BtVector3ToVector3Fast(v, out) \
	Vector_SetX(out, (v)->m_floats[0]); \
	Vector_SetY(out, (v)->m_floats[1]); \
	Vector_SetZ(out, (v)->m_floats[2]);

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

#define Vector3_IsFuzzyZero(v) btFuzzyZero(Vector_X(v)) && btFuzzyZero(Vector_Y(v)) && btFuzzyZero(Vector_Z(v))

#if defined(GRAPHICS_MONOGAME) || defined(GRAPHICS_NUMERICS) || defined(GRAPHICS_SHARPDX) || defined(GRAPHICS_SLIMDX)
#define Vector3_Length(v) (v).Length()
#else
#define Vector3_Length(v) (v).Length
#endif

#if defined(GRAPHICS_MOGRE)
#define Vector3_Cross(left, right, result) result = (left).CrossProduct(right)
#define Vector3_Dot(left, right) (left).DotProduct(right)
#define Vector3_Normalize(v) (v).Normalise()
#define Vector3_Zero Vector3::ZERO
#define Matrix_Identity Matrix4::IDENTITY
#define Matrix_Origin(m) (m)->GetTrans()
#elif defined(GRAPHICS_NUMERICS)
#define Vector3_Cross(left, right, result) result = Vector3::Cross(left, right)
#define Vector3_Dot(left, right) Vector3::Dot(left, right)
#define Vector3_Normalize(v) Vector3::Normalize(v)
#define Vector3_Zero Vector3::Zero
#define Matrix_Identity Matrix4x4::Identity
#define Matrix_Origin(m) (m).Translation
#else
#define Vector3_Cross(left, right, result) Vector3::Cross(left, right, result)
#define Vector3_Dot(left, right) Vector3::Dot(left, right)
#define Vector3_Normalize(v) (v).Normalize()
#define Vector3_Zero Vector3::Zero
#define Matrix_Identity Matrix::Identity
#ifdef GRAPHICS_OPENTK
#define Matrix_Origin(m) (m).ExtractTranslation()
#elif defined(GRAPHICS_GENERIC) || defined(GRAPHICS_OPENTK)
#define Matrix_Origin(m) (m).Origin
#elif defined(GRAPHICS_SHARPDX)
#define Matrix_Origin(m) (m).TranslationVector
#elif defined(GRAPHICS_MONOGAME)
#define Matrix_Origin(m) (m).Translation
#else
#define Matrix_Origin(m) Vector3((m).M41, (m).M42, (m).M43)
#endif
#endif
