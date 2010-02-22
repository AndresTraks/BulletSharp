#include "StdAfx.h"

#include "Math.h"

UsingFrameworkNamespace

using namespace BulletSharp;

Vector3 BulletSharp::Math::BtVec3ToVector3(const btVector3* vector)
{
	return Vector3(vector->m_floats[0], vector->m_floats[1], vector->m_floats[2]);
	//return Vector3(vector->getX(), vector->getY(), vector->getZ());
}
btVector3* BulletSharp::Math::Vector3ToBtVec3(Vector3 vector)
{
	return new btVector3(vector.X, vector.Y, vector.Z);
}

Quaternion BulletSharp::Math::BtQuatToQuaternion(const btQuaternion* quat)
{
	return Quaternion(quat->getX(), quat->getY(), quat->getZ(), quat->getW());
	//return Quaternion(quat->m_floats[0],quat->m_floats[1],quat->m_floats[2],quat->m_floats[3]);
}
btQuaternion* BulletSharp::Math::QuaternionToBtQuat(Quaternion quat)
{
	return new btQuaternion(quat.X, quat.Y, quat.Z, quat.W);
}

Matrix BulletSharp::Math::BtTransformToMatrix(const btTransform* transform)
{
	btScalar m[15];
	Matrix^ t = Matrix();

	transform->getOpenGLMatrix(m);

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
}

btTransform* BulletSharp::Math::MatrixToBtTransform(Matrix matrix)
{
	btScalar m[15];
	btTransform* t = new btTransform;

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

	t->setFromOpenGLMatrix(m);

	return t;
}
