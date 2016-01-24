#include "StdAfx.h"

#include "Math.h"

int* BulletSharp::Math::IntArrayToUnmanaged(array<int>^ i)
{
	int length = i->Length;
	int* intArray = new int[length];
	pin_ptr<int> iPtr = &i[0];
	memcpy(intArray, iPtr, length * sizeof(int));
	//for(int i=0; i<length; i++)
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
	int length = s->Length;
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


btVector3* BulletSharp::Math::Vector3ToBtVector3(Vector3% vector)
{
	btScalar x = Vector_X(vector);
	btScalar y = Vector_Y(vector);
	btScalar z = Vector_Z(vector);
	return ALIGNED_NEW(btVector3) (x, y, z);
}
void BulletSharp::Math::Vector3ToBtVector3(Vector3% vector, btVector3* vectorOut)
{
	btScalar* vo = (btScalar*)vectorOut;
	vo[0] = Vector_X(vector);
	vo[1] = Vector_Y(vector);
	vo[2] = Vector_Z(vector);
}

btVector3* BulletSharp::Math::Vector3ArrayToUnmanaged(array<Vector3>^ v)
{
	int length = v->Length;
	btVector3* btVertices = new btVector3[length];
	if (sizeof(btVector3) == sizeof(Vector3))
	{
		pin_ptr<Vector3> vPtr = &v[0];
		memcpy(btVertices, vPtr, length * sizeof(btVector3));
	}
	else
	{
		for(int i=0; i < length; i++)
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
	return new btVector4(Vector_X(vector), Vector_Y(vector), Vector_Z(vector), Vector_W(vector));
}
void BulletSharp::Math::Vector4ToBtVector4(Vector4 vector, btVector4* vectorOut)
{
	vectorOut->setValue(Vector_X(vector), Vector_Y(vector), Vector_Z(vector), Vector_W(vector));
}


Quaternion BulletSharp::Math::BtQuatToQuaternion(const btQuaternion* quat)
{
#ifdef GRAPHICS_MOGRE
	return Quaternion(quat->getW(), quat->getX(), quat->getY(), quat->getZ());
#else
	return Quaternion(quat->getX(), quat->getY(), quat->getZ(), quat->getW());
	//return Quaternion(quat->m_floats[0],quat->m_floats[1],quat->m_floats[2],quat->m_floats[3]);
#endif
}
btQuaternion* BulletSharp::Math::QuaternionToBtQuat(Quaternion quat)
{
	return ALIGNED_NEW(btQuaternion) (Vector_X(quat), Vector_Y(quat), Vector_Z(quat), Vector_W(quat));
}
void BulletSharp::Math::QuaternionToBtQuat(Quaternion quat, btQuaternion* outQuat)
{
	outQuat->setX(Vector_X(quat));
	outQuat->setY(Vector_Y(quat));
	outQuat->setZ(Vector_Z(quat));
	outQuat->setW(Vector_W(quat));
}


Matrix BulletSharp::Math::BtTransformToMatrix(const btTransform* transform)
{
#ifdef GRAPHICS_MOGRE
	btScalar* m = (btScalar*)transform;
	Matrix t = gcnew Mogre::Matrix4();
	t->m00 = m[0];
	t->m01 = m[1];
	t->m02 = m[2];
	t->m30 = 0;
	t->m10 = m[4];
	t->m11 = m[5];
	t->m12 = m[6];
	t->m31 = 0;
	t->m20 = m[8];
	t->m21 = m[9];
	t->m22 = m[10];
	t->m32 = 0;
	t->m03 = m[12];
	t->m13 = m[13];
	t->m23 = m[14];
	t->m33 = 1;

#else

	Matrix t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)transform;
	t.M11 = (float)m[0];
	t.M12 = (float)m[4];
	t.M13 = (float)m[8];
	t.M21 = (float)m[1];
	t.M22 = (float)m[5];
	t.M23 = (float)m[9];
	t.M31 = (float)m[2];
	t.M32 = (float)m[6];
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
#ifdef GRAPHICS_MOGRE
	t = gcnew Mogre::Matrix4();
	btScalar* m = (btScalar*)transform;
	t->m00 = m[0];
	t->m01 = m[1];
	t->m02 = m[2];
	t->m30 = 0;
	t->m10 = m[4];
	t->m11 = m[5];
	t->m12 = m[6];
	t->m13 = 0;
	t->m02 = m[8];
	t->m21 = m[9];
	t->m22 = m[10];
	t->m23 = 0;
	t->m03 = m[12];
	t->m13 = m[13];
	t->m23 = m[14];
	t->m33 = 1;

#else
	t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)transform;
	t.M11 = (float)m[0];
	t.M21 = (float)m[1];
	t.M31 = (float)m[2];
	t.M12 = (float)m[4];
	t.M22 = (float)m[5];
	t.M32 = (float)m[6];
	t.M13 = (float)m[8];
	t.M23 = (float)m[9];
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
	btTransform* t = ALIGNED_NEW(btTransform);

#ifdef GRAPHICS_MOGRE
	btScalar* m = (btScalar*)t;
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
	m[12] = matrix->m03;
	m[13] = matrix->m13;
	m[14] = matrix->m23;
	m[15] = 1;
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)t;
	m[0] = matrix.M11;
	m[1] = matrix.M21;
	m[2] = matrix.M31;
	m[3] = 0;
	m[4] = matrix.M12;
	m[5] = matrix.M22;
	m[6] = matrix.M32;
	m[7] = 0;
	m[8] = matrix.M13;
	m[9] = matrix.M23;
	m[10] = matrix.M33;
	m[11] = 0;
	m[12] = matrix.M41;
	m[13] = matrix.M42;
	m[14] = matrix.M43;
	m[15] = 1;
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLMatrix((btScalar*)mPtr);
#endif

#endif

	return t;
}

void BulletSharp::Math::MatrixToBtTransform(Matrix matrix, btTransform* t)
{
#ifdef GRAPHICS_MOGRE
	btScalar* m = (btScalar*)t;
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
	m[12] = matrix->m03;
	m[13] = matrix->m13;
	m[14] = matrix->m23;
	m[15] = 1;
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)t;
	m[0] = matrix.M11;
	m[1] = matrix.M21;
	m[2] = matrix.M31;
	m[3] = 0;
	m[4] = matrix.M12;
	m[5] = matrix.M22;
	m[6] = matrix.M32;
	m[7] = 0;
	m[8] = matrix.M13;
	m[9] = matrix.M23;
	m[10] = matrix.M33;
	m[11] = 0;
	m[12] = matrix.M41;
	m[13] = matrix.M42;
	m[14] = matrix.M43;
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLMatrix((btScalar*)mPtr);
	return;
#endif

#endif
}


Matrix BulletSharp::Math::BtMatrix3x3ToMatrix(const btMatrix3x3* matrix)
{
#ifdef GRAPHICS_MOGRE
	Matrix t = gcnew Mogre::Matrix4();
	btScalar* m = (btScalar*)matrix;
	t->m00 = m[0];
	t->m10 = m[4];
	t->m20 = m[8];
	t->m30 = 0;
	t->m01 = m[1];
	t->m11 = m[5];
	t->m21 = m[9];
	t->m31 = 0;
	t->m02 = m[2];
	t->m12 = m[6];
	t->m22 = m[10];
	t->m32 = 0;
	t->m03 = 0;
	t->m13 = 0;
	t->m23 = 0;
	t->m33 = 1;
#else

	Matrix t = Matrix();
#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)matrix;
	t.M11 = (float)m[0];
	t.M21 = (float)m[1];
	t.M31 = (float)m[2];
	t.M12 = (float)m[4];
	t.M22 = (float)m[5];
	t.M32 = (float)m[6];
	t.M13 = (float)m[8];
	t.M23 = (float)m[9];
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
	btMatrix3x3* t = ALIGNED_NEW(btMatrix3x3);

#ifdef GRAPHICS_MOGRE
	btScalar* m = (btScalar*)t;
	m[0] = matrix->m00;
	m[1] = matrix->m01;
	m[2] = matrix->m02;
	m[4] = matrix->m10;
	m[5] = matrix->m11;
	m[6] = matrix->m11;
	m[8] = matrix->m20;
	m[9] = matrix->m21;
	m[10] = matrix->m22;
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)t;
	m[0] = matrix.M11;
	m[1] = matrix.M21;
	m[2] = matrix.M31;
	m[4] = matrix.M12;
	m[5] = matrix.M22;
	m[6] = matrix.M32;
	m[8] = matrix.M13;
	m[9] = matrix.M23;
	m[10] = matrix.M33;
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLSubMatrix((btScalar*)mPtr);
#endif

#endif
	return t;
}

void BulletSharp::Math::MatrixToBtMatrix3x3(Matrix matrix, btMatrix3x3* t)
{
#ifdef GRAPHICS_MOGRE
	btScalar* m = (btScalar*)t;
	m[0] = matrix->m00;
	m[1] = matrix->m01;
	m[2] = matrix->m02;
	m[4] = matrix->m10;
	m[5] = matrix->m11;
	m[6] = matrix->m12;
	m[8] = matrix->m20;
	m[9] = matrix->m21;
	m[10] = matrix->m22;
#else

#ifdef GRAPHICS_NO_DIRECT_CAST
	btScalar* m = (btScalar*)t;
	m[0] = matrix.M11;
	m[1] = matrix.M21;
	m[2] = matrix.M31;
	m[4] = matrix.M12;
	m[5] = matrix.M22;
	m[6] = matrix.M32;
	m[8] = matrix.M13;
	m[9] = matrix.M23;
	m[10] = matrix.M33;
#else
	pin_ptr<Matrix> mPtr = &matrix;
	t->setFromOpenGLSubMatrix((btScalar*)mPtr);
#endif

#endif
}
