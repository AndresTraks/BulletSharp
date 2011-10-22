#include "StdAfx.h"

#include "Math.h"

int* BulletSharp::Math::IntArrayToUnmanaged(array<int>^ i)
{
	int* intArray = new int[i->Length];
	pin_ptr<int> iPtr = &i[0];
	memcpy(intArray, iPtr, i->Length * sizeof(int));
	//for(int i=0; i<i->Length; i++)
	//  intArray[i] = i[i];
	return intArray;
}

int* BulletSharp::Math::IntArrayToUnmanaged(array<int>^ i, int length)
{
	int* intArray = new int[length];
	pin_ptr<int> iPtr = &i[0];
	memcpy(intArray, iPtr, length * sizeof(int));
	//for(int i=0; i<length; i++)
	//  intArray[i] = i[i];
	return intArray;
}


btScalar* BulletSharp::Math::BtScalarArrayToUnmanaged(array<btScalar>^ s)
{
	btScalar* btScalars = new btScalar[s->Length];
#ifdef GRAPHICS_NO_DIRECT_CAST
	for(int i=0; i<s->Length; i++)
		btScalars[i] = s[i];
#else
	pin_ptr<btScalar> sPtr = &s[0];
	memcpy(btScalars, sPtr, s->Length * sizeof(btScalar));
#endif
	return btScalars;
}

btScalar* BulletSharp::Math::BtScalarArrayToUnmanaged(array<btScalar>^ s, int length)
{
	btScalar* btScalars = new btScalar[length];
#ifdef GRAPHICS_NO_DIRECT_CAST
	for(int i=0; i<length; i++)
		btScalars[i] = s[i];
#else
	pin_ptr<btScalar> sPtr = &s[0];
	memcpy(btScalars, sPtr, length * sizeof(btScalar));
#endif
	return btScalars;
}


void BulletSharp::Math::BtVector3ToVector3(const btVector3* vector, [Out] Vector3% vectorOut)
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
	vectorOut->setValue(vector.x, vector.y, vector.z);
#else
	vectorOut->setValue(vector.X, vector.Y, vector.Z);
#endif
}

btVector3* BulletSharp::Math::Vector3ArrayToUnmanaged(array<Vector3>^ v)
{
	btVector3* btVertices = new btVector3[v->Length];
	if (sizeof(btVector3) == sizeof(Vector3))
	{
		pin_ptr<Vector3> vPtr = &v[0];
		memcpy(btVertices, vPtr, v->Length * sizeof(btVector3));
	}
	else
	{
		int len = v->Length;
		for(int i=0; i < len; i++)
			Vector3ToBtVector3(v[i], &btVertices[i]);
	}
	return btVertices;
}

array<Vector3>^ BulletSharp::Math::Vector3ArrayToManaged(btVector3* v, int length)
{
	array<Vector3>^ vertices = gcnew array<Vector3>(length);
	if (sizeof(btVector3) == sizeof(Vector3))
	{
		pin_ptr<Vector3> vPtr = &vertices[0];
		memcpy(vPtr, v, length * sizeof(btVector3));
	}
	else
	{
		for(int i=0; i<length; i++)
			vertices[i] = BtVector3ToVector3(&v[i]);
	}
	return vertices;
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
	vectorOut->setValue(vector.x, vector.y, vector.z, vector.w);
#else
	vectorOut->setValue(vector.X, vector.Y, vector.Z, vector.W);
#endif
}


Quaternion BulletSharp::Math::BtQuatToQuaternion(const btQuaternion* quat)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	return Quaternion(quat->getW(), quat->getX(), quat->getY(), quat->getZ());
#else
	return Quaternion(quat->getX(), quat->getY(), quat->getZ(), quat->getW());
	//return Quaternion(quat->m_floats[0],quat->m_floats[1],quat->m_floats[2],quat->m_floats[3]);
#endif
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
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[16];
	transform->getOpenGLMatrix(m);

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

#else

	Matrix t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[16];
	transform->getOpenGLMatrix(m);

	t.M11 = (float)m[0];
	t.M12 = (float)m[1];
	t.M13 = (float)m[2];
	t.M21 = (float)m[4];
	t.M22 = (float)m[5];
	t.M23 = (float)m[6];
	t.M31 = (float)m[8];
	t.M32 = (float)m[9];
	t.M33 = (float)m[10];
	t.M41 = (float)m[12];
	t.M42 = (float)m[13];
	t.M43 = (float)m[14];
	t.M44 = 1;
#else
	pin_ptr<Matrix> mPtr = &t;
	transform->getOpenGLMatrix((btScalar*)mPtr);
#endif

#endif

	return t;
}

void BulletSharp::Math::BtTransformToMatrix(const btTransform* transform, [Out] Matrix% t)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[16];
	transform->getOpenGLMatrix(m);

#ifdef GRAPHICS_MOGRE
	t = gcnew Mogre::Matrix4();
#else
	t = gcnew Axiom::Math::Matrix4();
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

#else

	t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[16];
	transform->getOpenGLMatrix(m);

	t.M11 = (float)m[0];
	t.M12 = (float)m[1];
	t.M13 = (float)m[2];
	t.M21 = (float)m[4];
	t.M22 = (float)m[5];
	t.M23 = (float)m[6];
	t.M31 = (float)m[8];
	t.M32 = (float)m[9];
	t.M33 = (float)m[10];
	t.M41 = (float)m[12];
	t.M42 = (float)m[13];
	t.M43 = (float)m[14];
	t.M44 = 1;
#else
	pin_ptr<Matrix> mPtr = &t;
	transform->getOpenGLMatrix((btScalar*)mPtr);
#endif

#endif
}

btTransform* BulletSharp::Math::MatrixToBtTransform(Matrix matrix)
{
	btTransform* t = new btTransform;

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[16];

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

	t->setFromOpenGLMatrix(m);

#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[16];

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
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLMatrix((btScalar*)mPtr);
#endif

#endif

	return t;
}

void BulletSharp::Math::MatrixToBtTransform(Matrix matrix, btTransform* t)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btMatrix3x3* basis = new btMatrix3x3;
	btVector3* vector;

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

	t->setBasis(*basis);
	delete basis;

	t->setOrigin(*vector);
	delete vector;
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btMatrix3x3* basis = new btMatrix3x3(
		matrix.M11, matrix.M21, matrix.M31,
		matrix.M12, matrix.M22, matrix.M32,
		matrix.M13, matrix.M23, matrix.M33);
	t->setBasis(*basis);
	delete basis;
	
	btVector3* vector = new btVector3(matrix.M41, matrix.M42, matrix.M43);
	t->setOrigin(*vector);
	delete vector;
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLMatrix((btScalar*)mPtr);
	return;
#endif

#endif
}


Matrix BulletSharp::Math::BtMatrix3x3ToMatrix(const btMatrix3x3* matrix)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[12];
	matrix->getOpenGLSubMatrix(m);

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
#else

	Matrix t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[12];
	matrix->getOpenGLSubMatrix(m);

	t.M11 = (float)m[0];
	t.M12 = (float)m[1];
	t.M13 = (float)m[2];
	t.M21 = (float)m[4];
	t.M22 = (float)m[5];
	t.M23 = (float)m[6];
	t.M31 = (float)m[8];
	t.M32 = (float)m[9];
	t.M33 = (float)m[10];
	t.M44 = 1;
#else
	pin_ptr<Matrix> mPtr = &t;
	matrix->getOpenGLSubMatrix((btScalar*)mPtr);
	t.M44 = 1;
#endif

#endif
	return t;
}

btMatrix3x3* BulletSharp::Math::MatrixToBtMatrix3x3(Matrix matrix)
{
	btMatrix3x3* t = new btMatrix3x3;

#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[11];

	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;
	t->setFromOpenGLSubMatrix(m);

#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[12];

	m[0] = matrix.M11;
	m[1] = matrix.M12;
	m[2] = matrix.M13;
	m[4] = matrix.M21;
	m[5] = matrix.M22;
	m[6] = matrix.M23;
	m[8] = matrix.M31;
	m[9] = matrix.M32;
	m[10] = matrix.M33;

	t->setFromOpenGLSubMatrix(m);
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLSubMatrix((btScalar*)mPtr);
#endif

#endif
	return t;
}

void BulletSharp::Math::MatrixToBtMatrix3x3(Matrix matrix, btMatrix3x3* t)
{
#if defined(GRAPHICS_MOGRE) || defined(GRAPHICS_AXIOM)
	btScalar m[12];

	m[0] = matrix->m00;
	m[1] = matrix->m10;
	m[2] = matrix->m20;
	m[4] = matrix->m01;
	m[5] = matrix->m11;
	m[6] = matrix->m21;
	m[8] = matrix->m02;
	m[9] = matrix->m12;
	m[10] = matrix->m22;

	t->setFromOpenGLSubMatrix(m);
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar m[12];

	m[0] = matrix.M11;
	m[1] = matrix.M12;
	m[2] = matrix.M13;
	m[4] = matrix.M21;
	m[5] = matrix.M22;
	m[6] = matrix.M23;
	m[8] = matrix.M31;
	m[9] = matrix.M32;
	m[10] = matrix.M33;

	t->setFromOpenGLSubMatrix(m);
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLSubMatrix((btScalar*)mPtr);
#endif

#endif
}
