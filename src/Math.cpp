#include "StdAfx.h"

#include "Math.h"

UsingFrameworkNamespace

using namespace BulletSharp;

btVector3* BulletSharp::Math::Vector3ToBtVector3(Vector3 vector)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	return new btVector3(vector.x, vector.y, vector.z);
#else
	return new btVector3(vector.X, vector.Y, vector.Z);
#endif
}
void BulletSharp::Math::Vector3ToBtVector3(Vector3 vector, btVector3* vectorOut)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	vectorOut->setX(vector.x);
	vectorOut->setY(vector.y);
	vectorOut->setZ(vector.z);
#else
	vectorOut->setX(vector.X);
	vectorOut->setY(vector.Y);
	vectorOut->setZ(vector.Z);
#endif
}

btVector4* BulletSharp::Math::Vector4ToBtVector4(Vector4 vector)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	return new btVector4(vector.x, vector.y, vector.z, vector.w);
#else
	return new btVector4(vector.X, vector.Y, vector.Z, vector.W);
#endif
}
void BulletSharp::Math::Vector4ToBtVector4(Vector4 vector, btVector4* vectorOut)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	vectorOut->setX(vector.x);
	vectorOut->setY(vector.y);
	vectorOut->setZ(vector.z);
	vectorOut->setW(vector.w);
#else
	vectorOut->setX(vector.X);
	vectorOut->setY(vector.Y);
	vectorOut->setZ(vector.Z);
	vectorOut->setW(vector.W);
#endif
}


Quaternion BulletSharp::Math::BtQuatToQuaternion(const btQuaternion* quat)
{
	return Quaternion(quat->getX(), quat->getY(), quat->getZ(), quat->getW());
	//return Quaternion(quat->m_floats[0],quat->m_floats[1],quat->m_floats[2],quat->m_floats[3]);
}
btQuaternion* BulletSharp::Math::QuaternionToBtQuat(Quaternion quat)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	return new btQuaternion(quat.x, quat.y, quat.z, quat.w);
#else
	return new btQuaternion(quat.X, quat.Y, quat.Z, quat.W);
#endif
}


Matrix BulletSharp::Math::BtTransformToMatrix(const btTransform* transform)
{
	btScalar m[15];
	transform->getOpenGLMatrix(m);

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
#ifdef GRAPHICS_MOGRE
	Matrix t = gcnew Mogre::Matrix4();
#else
	Matrix t = gcnew Axiom::Math::Matrix4();
#endif

	t->m00 = m[0];
	t->m10 = m[1];
	t->m20 = m[2];
	t->m30 = 0;
	t->m01 = m[4];
	t->m11 = m[5];
	t->m21 = m[6];
	t->m31 = 0;
	t->m02 = m[8];
	t->m12 = m[9];
	t->m22 = m[10];
	t->m32 = 0;
	t->m03 = m[12];
	t->m13 = m[13];
	t->m23 = m[14];
	t->m33 = 1;

	return t;
#else
	Matrix^ t = Matrix();

	t->M11 = m[0];
	t->M12 = m[1];
	t->M13 = m[2];
	t->M14 = 0;
	t->M21 = m[4];
	t->M22 = m[5];
	t->M23 = m[6];
	t->M24 = 0;
	t->M31 = m[8];
	t->M32 = m[9];
	t->M33 = m[10];
	t->M34 = 0;
	t->M41 = m[12];
	t->M42 = m[13];
	t->M43 = m[14];
	t->M44 = 1;

	return *t;
#endif
}

btTransform* BulletSharp::Math::MatrixToBtTransform(Matrix matrix)
{
	btScalar m[15];
	btTransform* t = new btTransform;

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[3] = 0;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[7] = 0;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;
	m[11] = 0;
	m[12] = matrix->m03;
	m[13] = matrix->m13;
	m[14] = matrix->m23;
	m[15] = 1;
#else
	m[0] = matrix.M11;
	m[1] = matrix.M12;
	m[2] = matrix.M13;
	m[3] = 0;
	m[4] = matrix.M21;
	m[5] = matrix.M22;
	m[6] = matrix.M23;
	m[7] = 0;
	m[8] = matrix.M31;
	m[9] = matrix.M32;
	m[10] = matrix.M33;
	m[11] = 0;
	m[12] = matrix.M41;
	m[13] = matrix.M42;
	m[14] = matrix.M43;
	m[15] = 1;
#endif
	t->setFromOpenGLMatrix(m);

	return t;
}

void BulletSharp::Math::MatrixToBtTransform(Matrix matrix, btTransform* t)
{
	btMatrix3x3* basis;
	btVector3* vector;

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	basis = new btMatrix3x3();

	btScalar m[12];

	m[0] = matrix->m03;
	m[1] = matrix->m13;
	m[2] = matrix->m23;
	vector = new btVector3(m[0], m[1], m[2]);

	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[3] = 0;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[7] = 0;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;
	m[11] = 0;
	basis->setFromOpenGLSubMatrix(m);
#else
	basis = new btMatrix3x3(
		matrix.M11, matrix.M21, matrix.M31,
		matrix.M12, matrix.M22, matrix.M32,
		matrix.M13, matrix.M23, matrix.M33);
	vector = new btVector3(matrix.M41, matrix.M42, matrix.M43);
#endif

	t->setBasis(*basis);
	delete basis;

	t->setOrigin(*vector);
	delete vector;
}


Matrix BulletSharp::Math::BtMatrix3x3ToMatrix(const btMatrix3x3* matrix)
{
	btScalar m[12];
	matrix->getOpenGLSubMatrix(m);

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
#ifdef GRAPHICS_MOGRE
	Matrix t = gcnew Mogre::Matrix4();
#else
	Matrix t = gcnew Axiom::Math::Matrix4();
#endif

	t->m00 = m[0];
	t->m10 = m[1];
	t->m20 = m[2];
	t->m30 = 0;
	t->m01 = m[4];
	t->m11 = m[5];
	t->m21 = m[6];
	t->m31 = 0;
	t->m02 = m[8];
	t->m12 = m[9];
	t->m22 = m[10];
	t->m32 = 0;
	t->m03 = 0;
	t->m13 = 0;
	t->m23 = 0;
	t->m33 = 1;

	return t;
#else
	Matrix^ t = Matrix();

	t->M11 = m[0];
	t->M12 = m[1];
	t->M13 = m[2];
	t->M14 = 0;
	t->M21 = m[4];
	t->M22 = m[5];
	t->M23 = m[6];
	t->M24 = 0;
	t->M31 = m[8];
	t->M32 = m[9];
	t->M33 = m[10];
	t->M34 = 0;
	t->M41 = 0;
	t->M42 = 0;
	t->M43 = 0;
	t->M44 = 1;

	return *t;
#endif
}

btMatrix3x3* BulletSharp::Math::MatrixToBtMatrix3x3(Matrix matrix)
{
	btScalar m[11];
	btMatrix3x3* t = new btMatrix3x3;

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;
#else
	m[0] = matrix.M11;
	m[1] = matrix.M12;
	m[2] = matrix.M13;
	m[4] = matrix.M21;
	m[5] = matrix.M22;
	m[6] = matrix.M23;
	m[8] = matrix.M31;
	m[9] = matrix.M32;
	m[10] = matrix.M33;
#endif

	t->setFromOpenGLSubMatrix(m);
	return t;
}

void BulletSharp::Math::MatrixToBtMatrix3x3(Matrix matrix, btMatrix3x3* t)
{
	btScalar m[12];

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;
#else
	m[0] = matrix.M11;
	m[1] = matrix.M12;
	m[2] = matrix.M13;
	m[4] = matrix.M21;
	m[5] = matrix.M22;
	m[6] = matrix.M23;
	m[8] = matrix.M31;
	m[9] = matrix.M32;
	m[10] = matrix.M33;
#endif

	t->setFromOpenGLSubMatrix(m);
}
