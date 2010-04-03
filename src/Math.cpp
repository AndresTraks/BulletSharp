#include "StdAfx.h"

#include "Math.h"

UsingFrameworkNamespace

using namespace BulletSharp;

Vector3 BulletSharp::Math::BtVector3ToVector3(const btVector3* vector)
{
	return Vector3(vector->m_floats[0], vector->m_floats[1], vector->m_floats[2]);
	//return Vector3(vector->getX(), vector->getY(), vector->getZ());
}
btVector3* BulletSharp::Math::Vector3ToBtVector3(Vector3 vector)
{
#ifdef GRAPHICS_MOGRE
	return new btVector3(vector.x, vector.y, vector.z);
#else
	return new btVector3(vector.X, vector.Y, vector.Z);
#endif
}
void BulletSharp::Math::Vector3ToBtVector3(Vector3 vector, btVector3* vectorOut)
{
#ifdef GRAPHICS_MOGRE
	vectorOut->setX(vector.x);
	vectorOut->setY(vector.y);
	vectorOut->setZ(vector.z);
#else
	vectorOut->setX(vector.X);
	vectorOut->setY(vector.Y);
	vectorOut->setZ(vector.Z);
#endif
}

Quaternion BulletSharp::Math::BtQuatToQuaternion(const btQuaternion* quat)
{
	return Quaternion(quat->getX(), quat->getY(), quat->getZ(), quat->getW());
	//return Quaternion(quat->m_floats[0],quat->m_floats[1],quat->m_floats[2],quat->m_floats[3]);
}
btQuaternion* BulletSharp::Math::QuaternionToBtQuat(Quaternion quat)
{
#ifdef GRAPHICS_MOGRE
	return new btQuaternion(quat.x, quat.y, quat.z, quat.w);
#else
	return new btQuaternion(quat.X, quat.Y, quat.Z, quat.W);
#endif
}

Matrix BulletSharp::Math::BtTransformToMatrix(const btTransform* transform)
{
	btScalar m[15];
	transform->getOpenGLMatrix(m);

#ifdef GRAPHICS_MOGRE
	Matrix t = gcnew Mogre::Matrix4();
	
	t->m00 = m[0];
	t->m01 = m[1];
	t->m02 = m[2];
	t->m03 = 0;
	t->m10 = m[4];
	t->m11 = m[5];
	t->m12 = m[6];
	t->m13 = 0;
	t->m20 = m[8];
	t->m21 = m[9];
	t->m22 = m[10];
	t->m23 = 0;
	t->m30 = m[12];
	t->m31 = m[13];
	t->m32 = m[14];
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

#ifdef GRAPHICS_MOGRE
	m[0] = matrix->m00;
	m[1] = matrix->m01;
	m[2] = matrix->m02;
	m[3] = 0;
	m[4] = matrix->m10;
	m[5] = matrix->m11;
	m[6] = matrix->m12;
	m[7] = 0;
	m[8] = matrix->m20;
	m[9] = matrix->m21;
	m[10] = matrix->m22;
	m[11] = 0;
	m[12] = matrix->m30;
	m[13] = matrix->m31;
	m[14] = matrix->m32;
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
	btScalar m[15];
	t = new btTransform;

#ifdef GRAPHICS_MOGRE
	m[0] = matrix->m00;
	m[1] = matrix->m01;
	m[2] = matrix->m02;
	m[3] = 0;
	m[4] = matrix->m10;
	m[5] = matrix->m11;
	m[6] = matrix->m12;
	m[7] = 0;
	m[8] = matrix->m20;
	m[9] = matrix->m21;
	m[10] = matrix->m22;
	m[11] = 0;
	m[12] = matrix->m30;
	m[13] = matrix->m31;
	m[14] = matrix->m32;
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
}
