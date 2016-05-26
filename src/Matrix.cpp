#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifdef GRAPHICS_GENERIC

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"

using namespace System;
using namespace System::Globalization;

namespace BulletSharp
{
	btScalar Matrix::default::get(int row, int column)
	{
		if (row < 0 || row > 3)
			throw gcnew ArgumentOutOfRangeException("row", "Rows and columns for matrices run from 0 to 3, inclusive.");

		if (column < 0 || column > 3)
			throw gcnew ArgumentOutOfRangeException("column", "Rows and columns for matrices run from 0 to 3, inclusive.");

		int index = row * 4 + column;
		switch (index)
		{
		case 0:  return M11;
		case 1:  return M12;
		case 2:  return M13;
		case 3:  return M14;
		case 4:  return M21;
		case 5:  return M22;
		case 6:  return M23;
		case 7:  return M24;
		case 8:  return M31;
		case 9:  return M32;
		case 10: return M33;
		case 11: return M34;
		case 12: return M41;
		case 13: return M42;
		case 14: return M43;
		case 15: return M44;
		}

		return 0.0f;
	}

	void Matrix::default::set(int row, int column, btScalar value)
	{
		if (row < 0 || row > 3)
			throw gcnew ArgumentOutOfRangeException("row", "Rows and columns for matrices run from 0 to 3, inclusive.");

		if (column < 0 || column > 3)
			throw gcnew ArgumentOutOfRangeException("column", "Rows and columns for matrices run from 0 to 3, inclusive.");

		int index = row * 4 + column;
		switch (index)
		{
		case 0:  M11 = value; break;
		case 1:  M12 = value; break;
		case 2:  M13 = value; break;
		case 3:  M14 = value; break;
		case 4:  M21 = value; break;
		case 5:  M22 = value; break;
		case 6:  M23 = value; break;
		case 7:  M24 = value; break;
		case 8:  M31 = value; break;
		case 9:  M32 = value; break;
		case 10: M33 = value; break;
		case 11: M34 = value; break;
		case 12: M41 = value; break;
		case 13: M42 = value; break;
		case 14: M43 = value; break;
		case 15: M44 = value; break;
		}
	}

	Vector4 Matrix::Rows::get(int row)
	{
		return Vector4(default[row, 0], default[row, 1], default[row, 2], default[row, 3]);
	}

	void Matrix::Rows::set(int row, Vector4 value)
	{
		default[row, 0] = value.X;
		default[row, 1] = value.Y;
		default[row, 2] = value.Z;
		default[row, 3] = value.W;
	}

	Vector4 Matrix::Columns::get(int column)
	{
		return Vector4(default[0, column], default[1, column], default[2, column], default[3, column]);
	}

	void Matrix::Columns::set(int column, Vector4 value)
	{
		default[0, column] = value.X;
		default[1, column] = value.Y;
		default[2, column] = value.Z;
		default[3, column] = value.W;
	}

	Vector3 Matrix::Origin::get()
	{
		return Vector3(M41, M42, M43);
	}

	void Matrix::Origin::set(Vector3 value)
	{
		M41 = value.X;
		M42 = value.Y;
		M43 = value.Z;
	}

	Matrix Matrix::Identity::get()
	{
		Matrix result;
		result.M11 = 1.0f;
		result.M22 = 1.0f;
		result.M33 = 1.0f;
		result.M44 = 1.0f;

		return result;
	}

	bool Matrix::IsIdentity::get()
	{
		if (M11 != 1.0f || M22 != 1.0f || M33 != 1.0f || M44 != 1.0f)
			return false;

		if (M12 != 0.0f || M13 != 0.0f || M14 != 0.0f ||
			M21 != 0.0f || M23 != 0.0f || M24 != 0.0f ||
			M31 != 0.0f || M32 != 0.0f || M34 != 0.0f ||
			M41 != 0.0f || M42 != 0.0f || M43 != 0.0f)
			return false;

		return true;
	}

	array<btScalar>^ Matrix::ToArray()
	{
		array<btScalar>^ result = gcnew array<btScalar>(16);
		result[0] = M11;
		result[1] = M12;
		result[2] = M13;
		result[3] = M14;
		result[4] = M21;
		result[5] = M22;
		result[6] = M23;
		result[7] = M24;
		result[8] = M31;
		result[9] = M32;
		result[10] = M33;
		result[11] = M34;
		result[12] = M41;
		result[13] = M42;
		result[14] = M43;
		result[15] = M44;

		return result;
	}

	btScalar Matrix::Determinant()
	{
		btScalar temp1 = (M33 * M44) - (M34 * M43);
		btScalar temp2 = (M32 * M44) - (M34 * M42);
		btScalar temp3 = (M32 * M43) - (M33 * M42);
		btScalar temp4 = (M31 * M44) - (M34 * M41);
		btScalar temp5 = (M31 * M43) - (M33 * M41);
		btScalar temp6 = (M31 * M42) - (M32 * M41);

		return ((((M11 * (((M22 * temp1) - (M23 * temp2)) + (M24 * temp3))) - (M12 * (((M21 * temp1) -
			(M23 * temp4)) + (M24 * temp5)))) + (M13 * (((M21 * temp2) - (M22 * temp4)) + (M24 * temp6)))) -
			(M14 * (((M21 * temp3) - (M22 * temp5)) + (M23 * temp6))));
	}

	Matrix Matrix::Add(Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 + right.M11;
		result.M12 = left.M12 + right.M12;
		result.M13 = left.M13 + right.M13;
		result.M14 = left.M14 + right.M14;
		result.M21 = left.M21 + right.M21;
		result.M22 = left.M22 + right.M22;
		result.M23 = left.M23 + right.M23;
		result.M24 = left.M24 + right.M24;
		result.M31 = left.M31 + right.M31;
		result.M32 = left.M32 + right.M32;
		result.M33 = left.M33 + right.M33;
		result.M34 = left.M34 + right.M34;
		result.M41 = left.M41 + right.M41;
		result.M42 = left.M42 + right.M42;
		result.M43 = left.M43 + right.M43;
		result.M44 = left.M44 + right.M44;
		return result;
	}

	void Matrix::Add(Matrix% left, Matrix% right, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = left.M11 + right.M11;
		r.M12 = left.M12 + right.M12;
		r.M13 = left.M13 + right.M13;
		r.M14 = left.M14 + right.M14;
		r.M21 = left.M21 + right.M21;
		r.M22 = left.M22 + right.M22;
		r.M23 = left.M23 + right.M23;
		r.M24 = left.M24 + right.M24;
		r.M31 = left.M31 + right.M31;
		r.M32 = left.M32 + right.M32;
		r.M33 = left.M33 + right.M33;
		r.M34 = left.M34 + right.M34;
		r.M41 = left.M41 + right.M41;
		r.M42 = left.M42 + right.M42;
		r.M43 = left.M43 + right.M43;
		r.M44 = left.M44 + right.M44;

		result = r;
	}

	Matrix Matrix::Subtract(Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 - right.M11;
		result.M12 = left.M12 - right.M12;
		result.M13 = left.M13 - right.M13;
		result.M14 = left.M14 - right.M14;
		result.M21 = left.M21 - right.M21;
		result.M22 = left.M22 - right.M22;
		result.M23 = left.M23 - right.M23;
		result.M24 = left.M24 - right.M24;
		result.M31 = left.M31 - right.M31;
		result.M32 = left.M32 - right.M32;
		result.M33 = left.M33 - right.M33;
		result.M34 = left.M34 - right.M34;
		result.M41 = left.M41 - right.M41;
		result.M42 = left.M42 - right.M42;
		result.M43 = left.M43 - right.M43;
		result.M44 = left.M44 - right.M44;
		return result;
	}

	void Matrix::Subtract(Matrix% left, Matrix% right, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = left.M11 - right.M11;
		r.M12 = left.M12 - right.M12;
		r.M13 = left.M13 - right.M13;
		r.M14 = left.M14 - right.M14;
		r.M21 = left.M21 - right.M21;
		r.M22 = left.M22 - right.M22;
		r.M23 = left.M23 - right.M23;
		r.M24 = left.M24 - right.M24;
		r.M31 = left.M31 - right.M31;
		r.M32 = left.M32 - right.M32;
		r.M33 = left.M33 - right.M33;
		r.M34 = left.M34 - right.M34;
		r.M41 = left.M41 - right.M41;
		r.M42 = left.M42 - right.M42;
		r.M43 = left.M43 - right.M43;
		r.M44 = left.M44 - right.M44;

		result = r;
	}

	Matrix Matrix::Negate(Matrix matrix)
	{
		Matrix result;
		result.M11 = -matrix.M11;
		result.M12 = -matrix.M12;
		result.M13 = -matrix.M13;
		result.M14 = -matrix.M14;
		result.M21 = -matrix.M21;
		result.M22 = -matrix.M22;
		result.M23 = -matrix.M23;
		result.M24 = -matrix.M24;
		result.M31 = -matrix.M31;
		result.M32 = -matrix.M32;
		result.M33 = -matrix.M33;
		result.M34 = -matrix.M34;
		result.M41 = -matrix.M41;
		result.M42 = -matrix.M42;
		result.M43 = -matrix.M43;
		result.M44 = -matrix.M44;
		return result;
	}

	void Matrix::Negate(Matrix% matrix, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = -matrix.M11;
		r.M12 = -matrix.M12;
		r.M13 = -matrix.M13;
		r.M14 = -matrix.M14;
		r.M21 = -matrix.M21;
		r.M22 = -matrix.M22;
		r.M23 = -matrix.M23;
		r.M24 = -matrix.M24;
		r.M31 = -matrix.M31;
		r.M32 = -matrix.M32;
		r.M33 = -matrix.M33;
		r.M34 = -matrix.M34;
		r.M41 = -matrix.M41;
		r.M42 = -matrix.M42;
		r.M43 = -matrix.M43;
		r.M44 = -matrix.M44;

		result = r;
	}

	Matrix Matrix::Multiply(Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = (left.M11 * right.M11) + (left.M12 * right.M21) + (left.M13 * right.M31) + (left.M14 * right.M41);
		result.M12 = (left.M11 * right.M12) + (left.M12 * right.M22) + (left.M13 * right.M32) + (left.M14 * right.M42);
		result.M13 = (left.M11 * right.M13) + (left.M12 * right.M23) + (left.M13 * right.M33) + (left.M14 * right.M43);
		result.M14 = (left.M11 * right.M14) + (left.M12 * right.M24) + (left.M13 * right.M34) + (left.M14 * right.M44);
		result.M21 = (left.M21 * right.M11) + (left.M22 * right.M21) + (left.M23 * right.M31) + (left.M24 * right.M41);
		result.M22 = (left.M21 * right.M12) + (left.M22 * right.M22) + (left.M23 * right.M32) + (left.M24 * right.M42);
		result.M23 = (left.M21 * right.M13) + (left.M22 * right.M23) + (left.M23 * right.M33) + (left.M24 * right.M43);
		result.M24 = (left.M21 * right.M14) + (left.M22 * right.M24) + (left.M23 * right.M34) + (left.M24 * right.M44);
		result.M31 = (left.M31 * right.M11) + (left.M32 * right.M21) + (left.M33 * right.M31) + (left.M34 * right.M41);
		result.M32 = (left.M31 * right.M12) + (left.M32 * right.M22) + (left.M33 * right.M32) + (left.M34 * right.M42);
		result.M33 = (left.M31 * right.M13) + (left.M32 * right.M23) + (left.M33 * right.M33) + (left.M34 * right.M43);
		result.M34 = (left.M31 * right.M14) + (left.M32 * right.M24) + (left.M33 * right.M34) + (left.M34 * right.M44);
		result.M41 = (left.M41 * right.M11) + (left.M42 * right.M21) + (left.M43 * right.M31) + (left.M44 * right.M41);
		result.M42 = (left.M41 * right.M12) + (left.M42 * right.M22) + (left.M43 * right.M32) + (left.M44 * right.M42);
		result.M43 = (left.M41 * right.M13) + (left.M42 * right.M23) + (left.M43 * right.M33) + (left.M44 * right.M43);
		result.M44 = (left.M41 * right.M14) + (left.M42 * right.M24) + (left.M43 * right.M34) + (left.M44 * right.M44);
		return result;
	}

	void Matrix::Multiply(Matrix% left, Matrix% right, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = (left.M11 * right.M11) + (left.M12 * right.M21) + (left.M13 * right.M31) + (left.M14 * right.M41);
		r.M12 = (left.M11 * right.M12) + (left.M12 * right.M22) + (left.M13 * right.M32) + (left.M14 * right.M42);
		r.M13 = (left.M11 * right.M13) + (left.M12 * right.M23) + (left.M13 * right.M33) + (left.M14 * right.M43);
		r.M14 = (left.M11 * right.M14) + (left.M12 * right.M24) + (left.M13 * right.M34) + (left.M14 * right.M44);
		r.M21 = (left.M21 * right.M11) + (left.M22 * right.M21) + (left.M23 * right.M31) + (left.M24 * right.M41);
		r.M22 = (left.M21 * right.M12) + (left.M22 * right.M22) + (left.M23 * right.M32) + (left.M24 * right.M42);
		r.M23 = (left.M21 * right.M13) + (left.M22 * right.M23) + (left.M23 * right.M33) + (left.M24 * right.M43);
		r.M24 = (left.M21 * right.M14) + (left.M22 * right.M24) + (left.M23 * right.M34) + (left.M24 * right.M44);
		r.M31 = (left.M31 * right.M11) + (left.M32 * right.M21) + (left.M33 * right.M31) + (left.M34 * right.M41);
		r.M32 = (left.M31 * right.M12) + (left.M32 * right.M22) + (left.M33 * right.M32) + (left.M34 * right.M42);
		r.M33 = (left.M31 * right.M13) + (left.M32 * right.M23) + (left.M33 * right.M33) + (left.M34 * right.M43);
		r.M34 = (left.M31 * right.M14) + (left.M32 * right.M24) + (left.M33 * right.M34) + (left.M34 * right.M44);
		r.M41 = (left.M41 * right.M11) + (left.M42 * right.M21) + (left.M43 * right.M31) + (left.M44 * right.M41);
		r.M42 = (left.M41 * right.M12) + (left.M42 * right.M22) + (left.M43 * right.M32) + (left.M44 * right.M42);
		r.M43 = (left.M41 * right.M13) + (left.M42 * right.M23) + (left.M43 * right.M33) + (left.M44 * right.M43);
		r.M44 = (left.M41 * right.M14) + (left.M42 * right.M24) + (left.M43 * right.M34) + (left.M44 * right.M44);

		result = r;
	}

	Matrix Matrix::Multiply(Matrix left, btScalar right)
	{
		Matrix result;
		result.M11 = left.M11 * right;
		result.M12 = left.M12 * right;
		result.M13 = left.M13 * right;
		result.M14 = left.M14 * right;
		result.M21 = left.M21 * right;
		result.M22 = left.M22 * right;
		result.M23 = left.M23 * right;
		result.M24 = left.M24 * right;
		result.M31 = left.M31 * right;
		result.M32 = left.M32 * right;
		result.M33 = left.M33 * right;
		result.M34 = left.M34 * right;
		result.M41 = left.M41 * right;
		result.M42 = left.M42 * right;
		result.M43 = left.M43 * right;
		result.M44 = left.M44 * right;
		return result;
	}

	void Matrix::Multiply(Matrix% left, btScalar right, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = left.M11 * right;
		r.M12 = left.M12 * right;
		r.M13 = left.M13 * right;
		r.M14 = left.M14 * right;
		r.M21 = left.M21 * right;
		r.M22 = left.M22 * right;
		r.M23 = left.M23 * right;
		r.M24 = left.M24 * right;
		r.M31 = left.M31 * right;
		r.M32 = left.M32 * right;
		r.M33 = left.M33 * right;
		r.M34 = left.M34 * right;
		r.M41 = left.M41 * right;
		r.M42 = left.M42 * right;
		r.M43 = left.M43 * right;
		r.M44 = left.M44 * right;

		result = r;
	}

	Matrix Matrix::Divide(Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 / right.M11;
		result.M12 = left.M12 / right.M12;
		result.M13 = left.M13 / right.M13;
		result.M14 = left.M14 / right.M14;
		result.M21 = left.M21 / right.M21;
		result.M22 = left.M22 / right.M22;
		result.M23 = left.M23 / right.M23;
		result.M24 = left.M24 / right.M24;
		result.M31 = left.M31 / right.M31;
		result.M32 = left.M32 / right.M32;
		result.M33 = left.M33 / right.M33;
		result.M34 = left.M34 / right.M34;
		result.M41 = left.M41 / right.M41;
		result.M42 = left.M42 / right.M42;
		result.M43 = left.M43 / right.M43;
		result.M44 = left.M44 / right.M44;
		return result;
	}

	void Matrix::Divide(Matrix% left, Matrix% right, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = left.M11 / right.M11;
		r.M12 = left.M12 / right.M12;
		r.M13 = left.M13 / right.M13;
		r.M14 = left.M14 / right.M14;
		r.M21 = left.M21 / right.M21;
		r.M22 = left.M22 / right.M22;
		r.M23 = left.M23 / right.M23;
		r.M24 = left.M24 / right.M24;
		r.M31 = left.M31 / right.M31;
		r.M32 = left.M32 / right.M32;
		r.M33 = left.M33 / right.M33;
		r.M34 = left.M34 / right.M34;
		r.M41 = left.M41 / right.M41;
		r.M42 = left.M42 / right.M42;
		r.M43 = left.M43 / right.M43;
		r.M44 = left.M44 / right.M44;

		result = r;
	}

	Matrix Matrix::Divide(Matrix left, btScalar right)
	{
		Matrix result;
		btScalar inv = 1.0f / right;

		result.M11 = left.M11 * inv;
		result.M12 = left.M12 * inv;
		result.M13 = left.M13 * inv;
		result.M14 = left.M14 * inv;
		result.M21 = left.M21 * inv;
		result.M22 = left.M22 * inv;
		result.M23 = left.M23 * inv;
		result.M24 = left.M24 * inv;
		result.M31 = left.M31 * inv;
		result.M32 = left.M32 * inv;
		result.M33 = left.M33 * inv;
		result.M34 = left.M34 * inv;
		result.M41 = left.M41 * inv;
		result.M42 = left.M42 * inv;
		result.M43 = left.M43 * inv;
		result.M44 = left.M44 * inv;
		return result;
	}

	void Matrix::Divide(Matrix% left, btScalar right, [Out] Matrix% result)
	{
		btScalar inv = 1.0f / right;

		Matrix r;
		r.M11 = left.M11 * inv;
		r.M12 = left.M12 * inv;
		r.M13 = left.M13 * inv;
		r.M14 = left.M14 * inv;
		r.M21 = left.M21 * inv;
		r.M22 = left.M22 * inv;
		r.M23 = left.M23 * inv;
		r.M24 = left.M24 * inv;
		r.M31 = left.M31 * inv;
		r.M32 = left.M32 * inv;
		r.M33 = left.M33 * inv;
		r.M34 = left.M34 * inv;
		r.M41 = left.M41 * inv;
		r.M42 = left.M42 * inv;
		r.M43 = left.M43 * inv;
		r.M44 = left.M44 * inv;

		result = r;
	}

	Matrix Matrix::Invert(Matrix m)
	{
		Matrix inv;
		btScalar det;

		inv.M11 = m.M22*m.M33*m.M44 - m.M22*m.M34*m.M43 - m.M32*m.M23*m.M44
			+ m.M32*m.M24*m.M43 + m.M42*m.M23*m.M34 - m.M42*m.M24*m.M33;
		inv.M21 = -m.M21*m.M33*m.M44 + m.M21*m.M34*m.M43 + m.M31*m.M23*m.M44
			- m.M31*m.M24*m.M43 - m.M41*m.M23*m.M34 + m.M41*m.M24*m.M33;
		inv.M31 = m.M21*m.M32*m.M44 - m.M21*m.M34*m.M42 - m.M31*m.M22*m.M44
			+ m.M31*m.M24*m.M42 + m.M41*m.M22*m.M34 - m.M41*m.M24*m.M32;
		inv.M41 = -m.M21*m.M32*m.M43 + m.M21*m.M33*m.M42 + m.M31*m.M22*m.M43
			- m.M31*m.M23*m.M42 - m.M41*m.M22*m.M33 + m.M41*m.M23*m.M32;
		inv.M12 = -m.M12*m.M33*m.M44 + m.M12*m.M34*m.M43 + m.M32*m.M13*m.M44
			- m.M32*m.M14*m.M43 - m.M42*m.M13*m.M34 + m.M42*m.M14*m.M33;
		inv.M22 = m.M11*m.M33*m.M44 - m.M11*m.M34*m.M43 - m.M31*m.M13*m.M44
			+ m.M31*m.M14*m.M43 + m.M41*m.M13*m.M34 - m.M41*m.M14*m.M33;
		inv.M32 = -m.M11*m.M32*m.M44 + m.M11*m.M34*m.M42 + m.M31*m.M12*m.M44
			- m.M31*m.M14*m.M42 - m.M41*m.M12*m.M34 + m.M41*m.M14*m.M32;
		inv.M42 = m.M11*m.M32*m.M43 - m.M11*m.M33*m.M42 - m.M31*m.M12*m.M43
			+ m.M31*m.M13*m.M42 + m.M41*m.M12*m.M33 - m.M41*m.M13*m.M32;
		inv.M13 = m.M12*m.M23*m.M44 - m.M12*m.M24*m.M43 - m.M22*m.M13*m.M44
			+ m.M22*m.M14*m.M43 + m.M42*m.M13*m.M24 - m.M42*m.M14*m.M23;
		inv.M23 = -m.M11*m.M23*m.M44 + m.M11*m.M24*m.M43 + m.M21*m.M13*m.M44
			- m.M21*m.M14*m.M43 - m.M41*m.M13*m.M24 + m.M41*m.M14*m.M23;
		inv.M33 = m.M11*m.M22*m.M44 - m.M11*m.M24*m.M42 - m.M21*m.M12*m.M44
			+ m.M21*m.M14*m.M42 + m.M41*m.M12*m.M24 - m.M41*m.M14*m.M22;
		inv.M43 = -m.M11*m.M22*m.M43 + m.M11*m.M23*m.M42 + m.M21*m.M12*m.M43
			- m.M21*m.M13*m.M42 - m.M41*m.M12*m.M23 + m.M41*m.M13*m.M22;
		inv.M14 = -m.M12*m.M23*m.M34 + m.M12*m.M24*m.M33 + m.M22*m.M13*m.M34
			- m.M22*m.M14*m.M33 - m.M32*m.M13*m.M24 + m.M32*m.M14*m.M23;
		inv.M24 = m.M11*m.M23*m.M34 - m.M11*m.M24*m.M33 - m.M21*m.M13*m.M34
			+ m.M21*m.M14*m.M33 + m.M31*m.M13*m.M24 - m.M31*m.M14*m.M23;
		inv.M34 = -m.M11*m.M22*m.M34 + m.M11*m.M24*m.M32 + m.M21*m.M12*m.M34
			- m.M21*m.M14*m.M32 - m.M31*m.M12*m.M24 + m.M31*m.M14*m.M22;
		inv.M44 = m.M11*m.M22*m.M33 - m.M11*m.M23*m.M32 - m.M21*m.M12*m.M33
			+ m.M21*m.M13*m.M32 + m.M31*m.M12*m.M23 - m.M31*m.M13*m.M22;

		det = m.M11*inv.M11 + m.M12*inv.M21 + m.M13*inv.M31 + m.M14*inv.M41;
		if (det == 0)
			return inv;

		det = btScalar(1.0) / det;

		return inv * det;
	}

	Matrix Matrix::Lerp(Matrix value1, Matrix value2, btScalar amount)
	{
		Matrix result;
		result.M11 = value1.M11 + ((value2.M11 - value1.M11) * amount);
		result.M12 = value1.M12 + ((value2.M12 - value1.M12) * amount);
		result.M13 = value1.M13 + ((value2.M13 - value1.M13) * amount);
		result.M14 = value1.M14 + ((value2.M14 - value1.M14) * amount);
		result.M21 = value1.M21 + ((value2.M21 - value1.M21) * amount);
		result.M22 = value1.M22 + ((value2.M22 - value1.M22) * amount);
		result.M23 = value1.M23 + ((value2.M23 - value1.M23) * amount);
		result.M24 = value1.M24 + ((value2.M24 - value1.M24) * amount);
		result.M31 = value1.M31 + ((value2.M31 - value1.M31) * amount);
		result.M32 = value1.M32 + ((value2.M32 - value1.M32) * amount);
		result.M33 = value1.M33 + ((value2.M33 - value1.M33) * amount);
		result.M34 = value1.M34 + ((value2.M34 - value1.M34) * amount);
		result.M41 = value1.M41 + ((value2.M41 - value1.M41) * amount);
		result.M42 = value1.M42 + ((value2.M42 - value1.M42) * amount);
		result.M43 = value1.M43 + ((value2.M43 - value1.M43) * amount);
		result.M44 = value1.M44 + ((value2.M44 - value1.M44) * amount);
		return result;
	}

	void Matrix::Lerp(Matrix% value1, Matrix% value2, btScalar amount, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = value1.M11 + ((value2.M11 - value1.M11) * amount);
		r.M12 = value1.M12 + ((value2.M12 - value1.M12) * amount);
		r.M13 = value1.M13 + ((value2.M13 - value1.M13) * amount);
		r.M14 = value1.M14 + ((value2.M14 - value1.M14) * amount);
		r.M21 = value1.M21 + ((value2.M21 - value1.M21) * amount);
		r.M22 = value1.M22 + ((value2.M22 - value1.M22) * amount);
		r.M23 = value1.M23 + ((value2.M23 - value1.M23) * amount);
		r.M24 = value1.M24 + ((value2.M24 - value1.M24) * amount);
		r.M31 = value1.M31 + ((value2.M31 - value1.M31) * amount);
		r.M32 = value1.M32 + ((value2.M32 - value1.M32) * amount);
		r.M33 = value1.M33 + ((value2.M33 - value1.M33) * amount);
		r.M34 = value1.M34 + ((value2.M34 - value1.M34) * amount);
		r.M41 = value1.M41 + ((value2.M41 - value1.M41) * amount);
		r.M42 = value1.M42 + ((value2.M42 - value1.M42) * amount);
		r.M43 = value1.M43 + ((value2.M43 - value1.M43) * amount);
		r.M44 = value1.M44 + ((value2.M44 - value1.M44) * amount);

		result = r;
	}

	Matrix Matrix::Billboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3 cameraForwardVector)
	{
		Matrix result;
		Vector3 difference = objectPosition - cameraPosition;
		Vector3 crossed;
		Vector3 final;

		btScalar lengthSq = difference.LengthSquared;
		if (lengthSq < 0.0001f)
			difference = -cameraForwardVector;
		else
			difference *= static_cast<btScalar>(1.0f / btSqrt(lengthSq));

		Vector3::Cross(cameraUpVector, difference, crossed);
		crossed.Normalize();
		Vector3::Cross(difference, crossed, final);

		result.M11 = final.X;
		result.M12 = final.Y;
		result.M13 = final.Z;
		result.M14 = 0.0f;
		result.M21 = crossed.X;
		result.M22 = crossed.Y;
		result.M23 = crossed.Z;
		result.M24 = 0.0f;
		result.M31 = difference.X;
		result.M32 = difference.Y;
		result.M33 = difference.Z;
		result.M34 = 0.0f;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::Billboard(Vector3% objectPosition, Vector3% cameraPosition, Vector3% cameraUpVector, Vector3% cameraForwardVector, [Out] Matrix% result)
	{
		Vector3 difference = objectPosition - cameraPosition;
		Vector3 crossed;
		Vector3 final;

		btScalar lengthSq = difference.LengthSquared;
		if (lengthSq < 0.0001f)
			difference = -cameraForwardVector;
		else
			difference *= static_cast<btScalar>(1.0f / btSqrt(lengthSq));

		Vector3::Cross(cameraUpVector, difference, crossed);
		crossed.Normalize();
		Vector3::Cross(difference, crossed, final);

		result.M11 = final.X;
		result.M12 = final.Y;
		result.M13 = final.Z;
		result.M14 = 0.0f;
		result.M21 = crossed.X;
		result.M22 = crossed.Y;
		result.M23 = crossed.Z;
		result.M24 = 0.0f;
		result.M31 = difference.X;
		result.M32 = difference.Y;
		result.M33 = difference.Z;
		result.M34 = 0.0f;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1.0f;
	}

	Matrix Matrix::LookAtLH(Vector3 eye, Vector3 target, Vector3 up)
	{
		Matrix result;

		Vector3 zaxis = Vector3::Normalize(target - eye);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
		Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

		result.M11 = xaxis.X;
		result.M12 = yaxis.X;
		result.M13 = zaxis.X;
		result.M14 = 0.0f;
		result.M21 = xaxis.Y;
		result.M22 = yaxis.Y;
		result.M23 = zaxis.Y;
		result.M24 = 0.0f;
		result.M31 = xaxis.Z;
		result.M32 = yaxis.Z;
		result.M33 = zaxis.Z;
		result.M34 = 0.0f;
		result.M41 = -Vector3::Dot(xaxis, eye);
		result.M42 = -Vector3::Dot(yaxis, eye);
		result.M43 = -Vector3::Dot(zaxis, eye);
		result.M44 = 1.0f;

		return result;
	}

	Matrix Matrix::RotationX(btScalar angle)
	{
		Matrix result;
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = cos;
		result.M23 = sin;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = -sin;
		result.M33 = cos;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::RotationX(btScalar angle, [Out] Matrix% result)
	{
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = cos;
		result.M23 = sin;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = -sin;
		result.M33 = cos;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationY(btScalar angle)
	{
		Matrix result;
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = cos;
		result.M12 = 0.0f;
		result.M13 = -sin;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = sin;
		result.M32 = 0.0f;
		result.M33 = cos;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::RotationY(btScalar angle, [Out] Matrix% result)
	{
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = cos;
		result.M12 = 0.0f;
		result.M13 = -sin;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = sin;
		result.M32 = 0.0f;
		result.M33 = cos;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationZ(btScalar angle)
	{
		Matrix result;
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = cos;
		result.M12 = sin;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = -sin;
		result.M22 = cos;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::RotationZ(btScalar angle, [Out] Matrix% result)
	{
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);

		result.M11 = cos;
		result.M12 = sin;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = -sin;
		result.M22 = cos;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationQuaternion(Quaternion quaternion)
	{
		Matrix result;

		btScalar xx = quaternion.X * quaternion.X;
		btScalar yy = quaternion.Y * quaternion.Y;
		btScalar zz = quaternion.Z * quaternion.Z;
		btScalar xy = quaternion.X * quaternion.Y;
		btScalar zw = quaternion.Z * quaternion.W;
		btScalar zx = quaternion.Z * quaternion.X;
		btScalar yw = quaternion.Y * quaternion.W;
		btScalar yz = quaternion.Y * quaternion.Z;
		btScalar xw = quaternion.X * quaternion.W;
		result.M11 = 1.0f - (2.0f * (yy + zz));
		result.M12 = 2.0f * (xy + zw);
		result.M13 = 2.0f * (zx - yw);
		result.M14 = 0.0f;
		result.M21 = 2.0f * (xy - zw);
		result.M22 = 1.0f - (2.0f * (zz + xx));
		result.M23 = 2.0f * (yz + xw);
		result.M24 = 0.0f;
		result.M31 = 2.0f * (zx + yw);
		result.M32 = 2.0f * (yz - xw);
		result.M33 = 1.0f - (2.0f * (yy + xx));
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::RotationQuaternion(Quaternion% rotation, [Out] Matrix% result)
	{
		btScalar xx = rotation.X * rotation.X;
		btScalar yy = rotation.Y * rotation.Y;
		btScalar zz = rotation.Z * rotation.Z;
		btScalar xy = rotation.X * rotation.Y;
		btScalar zw = rotation.Z * rotation.W;
		btScalar zx = rotation.Z * rotation.X;
		btScalar yw = rotation.Y * rotation.W;
		btScalar yz = rotation.Y * rotation.Z;
		btScalar xw = rotation.X * rotation.W;
		result.M11 = 1.0f - (2.0f * (yy + zz));
		result.M12 = 2.0f * (xy + zw);
		result.M13 = 2.0f * (zx - yw);
		result.M14 = 0.0f;
		result.M21 = 2.0f * (xy - zw);
		result.M22 = 1.0f - (2.0f * (zz + xx));
		result.M23 = 2.0f * (yz + xw);
		result.M24 = 0.0f;
		result.M31 = 2.0f * (zx + yw);
		result.M32 = 2.0f * (yz - xw);
		result.M33 = 1.0f - (2.0f * (yy + xx));
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationAxis(Vector3 axis, btScalar angle)
	{
		if (axis.LengthSquared != 1.0f)
			axis.Normalize();

		Matrix result;
		btScalar x = axis.X;
		btScalar y = axis.Y;
		btScalar z = axis.Z;
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);
		btScalar xx = x * x;
		btScalar yy = y * y;
		btScalar zz = z * z;
		btScalar xy = x * y;
		btScalar xz = x * z;
		btScalar yz = y * z;

		result.M11 = xx + (cos * (1.0f - xx));
		result.M12 = (xy - (cos * xy)) + (sin * z);
		result.M13 = (xz - (cos * xz)) - (sin * y);
		result.M14 = 0.0f;
		result.M21 = (xy - (cos * xy)) - (sin * z);
		result.M22 = yy + (cos * (1.0f - yy));
		result.M23 = (yz - (cos * yz)) + (sin * x);
		result.M24 = 0.0f;
		result.M31 = (xz - (cos * xz)) + (sin * y);
		result.M32 = (yz - (cos * yz)) - (sin * x);
		result.M33 = zz + (cos * (1.0f - zz));
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::RotationAxis(Vector3% axis, btScalar angle, [Out] Matrix% result)
	{
		if (axis.LengthSquared != 1.0f)
			axis.Normalize();

		btScalar x = axis.X;
		btScalar y = axis.Y;
		btScalar z = axis.Z;
		btScalar cos = btCos(angle);
		btScalar sin = btSin(angle);
		btScalar xx = x * x;
		btScalar yy = y * y;
		btScalar zz = z * z;
		btScalar xy = x * y;
		btScalar xz = x * z;
		btScalar yz = y * z;

		result.M11 = xx + (cos * (1.0f - xx));
		result.M12 = (xy - (cos * xy)) + (sin * z);
		result.M13 = (xz - (cos * xz)) - (sin * y);
		result.M14 = 0.0f;
		result.M21 = (xy - (cos * xy)) - (sin * z);
		result.M22 = yy + (cos * (1.0f - yy));
		result.M23 = (yz - (cos * yz)) + (sin * x);
		result.M24 = 0.0f;
		result.M31 = (xz - (cos * xz)) + (sin * y);
		result.M32 = (yz - (cos * yz)) - (sin * x);
		result.M33 = zz + (cos * (1.0f - zz));
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationYawPitchRoll(btScalar yaw, btScalar pitch, btScalar roll)
	{
		Matrix result;
		Quaternion quaternion;
		Quaternion::RotationYawPitchRoll(yaw, pitch, roll, quaternion);
		RotationQuaternion(quaternion, result);
		return result;
	}

	void Matrix::RotationYawPitchRoll(btScalar yaw, btScalar pitch, btScalar roll, [Out] Matrix% result)
	{
		Quaternion quaternion;
		Quaternion::RotationYawPitchRoll(yaw, pitch, roll, quaternion);
		RotationQuaternion(quaternion, result);
	}

	Matrix Matrix::Translation(btScalar x, btScalar y, btScalar z)
	{
		Matrix result;
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = x;
		result.M42 = y;
		result.M43 = z;
		result.M44 = 1.0f;
		return result;
	}

	void Matrix::Translation(btScalar x, btScalar y, btScalar z, [Out] Matrix% result)
	{
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = x;
		result.M42 = y;
		result.M43 = z;
		result.M44 = 1.0f;
	}

	Matrix Matrix::Translation(Vector3 translation)
	{
		Matrix result;
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = translation.X;
		result.M42 = translation.Y;
		result.M43 = translation.Z;
		result.M44 = 1.0f;
		return result;
	}

	void Matrix::Translation(Vector3% translation, [Out] Matrix% result)
	{
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = translation.X;
		result.M42 = translation.Y;
		result.M43 = translation.Z;
		result.M44 = 1.0f;
	}

	Matrix Matrix::Scaling(btScalar x, btScalar y, btScalar z)
	{
		Matrix result;
		result.M11 = x;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	}

	void Matrix::Scaling(btScalar x, btScalar y, btScalar z, [Out] Matrix% result)
	{
		result.M11 = x;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::Scaling(Vector3 scaling)
	{
		Matrix result;
		result.M11 = scaling.X;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = scaling.Y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = scaling.Z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	}

	void Matrix::Scaling(Vector3% scaling, [Out] Matrix% result)
	{
		result.M11 = scaling.X;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = scaling.Y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = scaling.Z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}

	Matrix Matrix::Transpose(Matrix mat)
	{
		Matrix result;
		result.M11 = mat.M11;
		result.M12 = mat.M21;
		result.M13 = mat.M31;
		result.M14 = mat.M41;
		result.M21 = mat.M12;
		result.M22 = mat.M22;
		result.M23 = mat.M32;
		result.M24 = mat.M42;
		result.M31 = mat.M13;
		result.M32 = mat.M23;
		result.M33 = mat.M33;
		result.M34 = mat.M43;
		result.M41 = mat.M14;
		result.M42 = mat.M24;
		result.M43 = mat.M34;
		result.M44 = mat.M44;
		return result;
	}

	void Matrix::Transpose(Matrix% mat, [Out] Matrix% result)
	{
		Matrix r;
		r.M11 = mat.M11;
		r.M12 = mat.M21;
		r.M13 = mat.M31;
		r.M14 = mat.M41;
		r.M21 = mat.M12;
		r.M22 = mat.M22;
		r.M23 = mat.M32;
		r.M24 = mat.M42;
		r.M31 = mat.M13;
		r.M32 = mat.M23;
		r.M33 = mat.M33;
		r.M34 = mat.M43;
		r.M41 = mat.M14;
		r.M42 = mat.M24;
		r.M43 = mat.M34;
		r.M44 = mat.M44;

		result = r;
	}

	Matrix Matrix::operator * (Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = (left.M11 * right.M11) + (left.M12 * right.M21) + (left.M13 * right.M31) + (left.M14 * right.M41);
		result.M12 = (left.M11 * right.M12) + (left.M12 * right.M22) + (left.M13 * right.M32) + (left.M14 * right.M42);
		result.M13 = (left.M11 * right.M13) + (left.M12 * right.M23) + (left.M13 * right.M33) + (left.M14 * right.M43);
		result.M14 = (left.M11 * right.M14) + (left.M12 * right.M24) + (left.M13 * right.M34) + (left.M14 * right.M44);
		result.M21 = (left.M21 * right.M11) + (left.M22 * right.M21) + (left.M23 * right.M31) + (left.M24 * right.M41);
		result.M22 = (left.M21 * right.M12) + (left.M22 * right.M22) + (left.M23 * right.M32) + (left.M24 * right.M42);
		result.M23 = (left.M21 * right.M13) + (left.M22 * right.M23) + (left.M23 * right.M33) + (left.M24 * right.M43);
		result.M24 = (left.M21 * right.M14) + (left.M22 * right.M24) + (left.M23 * right.M34) + (left.M24 * right.M44);
		result.M31 = (left.M31 * right.M11) + (left.M32 * right.M21) + (left.M33 * right.M31) + (left.M34 * right.M41);
		result.M32 = (left.M31 * right.M12) + (left.M32 * right.M22) + (left.M33 * right.M32) + (left.M34 * right.M42);
		result.M33 = (left.M31 * right.M13) + (left.M32 * right.M23) + (left.M33 * right.M33) + (left.M34 * right.M43);
		result.M34 = (left.M31 * right.M14) + (left.M32 * right.M24) + (left.M33 * right.M34) + (left.M34 * right.M44);
		result.M41 = (left.M41 * right.M11) + (left.M42 * right.M21) + (left.M43 * right.M31) + (left.M44 * right.M41);
		result.M42 = (left.M41 * right.M12) + (left.M42 * right.M22) + (left.M43 * right.M32) + (left.M44 * right.M42);
		result.M43 = (left.M41 * right.M13) + (left.M42 * right.M23) + (left.M43 * right.M33) + (left.M44 * right.M43);
		result.M44 = (left.M41 * right.M14) + (left.M42 * right.M24) + (left.M43 * right.M34) + (left.M44 * right.M44);
		return result;
	}

	Matrix Matrix::operator * (Matrix left, btScalar right)
	{
		Matrix result;
		result.M11 = left.M11 * right;
		result.M12 = left.M12 * right;
		result.M13 = left.M13 * right;
		result.M14 = left.M14 * right;
		result.M21 = left.M21 * right;
		result.M22 = left.M22 * right;
		result.M23 = left.M23 * right;
		result.M24 = left.M24 * right;
		result.M31 = left.M31 * right;
		result.M32 = left.M32 * right;
		result.M33 = left.M33 * right;
		result.M34 = left.M34 * right;
		result.M41 = left.M41 * right;
		result.M42 = left.M42 * right;
		result.M43 = left.M43 * right;
		result.M44 = left.M44 * right;
		return result;
	}

	Matrix Matrix::operator * (btScalar right, Matrix left)
	{
		return left * right;
	}

	Matrix Matrix::operator / (Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 / right.M11;
		result.M12 = left.M12 / right.M12;
		result.M13 = left.M13 / right.M13;
		result.M14 = left.M14 / right.M14;
		result.M21 = left.M21 / right.M21;
		result.M22 = left.M22 / right.M22;
		result.M23 = left.M23 / right.M23;
		result.M24 = left.M24 / right.M24;
		result.M31 = left.M31 / right.M31;
		result.M32 = left.M32 / right.M32;
		result.M33 = left.M33 / right.M33;
		result.M34 = left.M34 / right.M34;
		result.M41 = left.M41 / right.M41;
		result.M42 = left.M42 / right.M42;
		result.M43 = left.M43 / right.M43;
		result.M44 = left.M44 / right.M44;
		return result;
	}

	Matrix Matrix::operator / (Matrix left, btScalar right)
	{
		Matrix result;
		result.M11 = left.M11 / right;
		result.M12 = left.M12 / right;
		result.M13 = left.M13 / right;
		result.M14 = left.M14 / right;
		result.M21 = left.M21 / right;
		result.M22 = left.M22 / right;
		result.M23 = left.M23 / right;
		result.M24 = left.M24 / right;
		result.M31 = left.M31 / right;
		result.M32 = left.M32 / right;
		result.M33 = left.M33 / right;
		result.M34 = left.M34 / right;
		result.M41 = left.M41 / right;
		result.M42 = left.M42 / right;
		result.M43 = left.M43 / right;
		result.M44 = left.M44 / right;
		return result;
	}

	Matrix Matrix::operator + (Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 + right.M11;
		result.M12 = left.M12 + right.M12;
		result.M13 = left.M13 + right.M13;
		result.M14 = left.M14 + right.M14;
		result.M21 = left.M21 + right.M21;
		result.M22 = left.M22 + right.M22;
		result.M23 = left.M23 + right.M23;
		result.M24 = left.M24 + right.M24;
		result.M31 = left.M31 + right.M31;
		result.M32 = left.M32 + right.M32;
		result.M33 = left.M33 + right.M33;
		result.M34 = left.M34 + right.M34;
		result.M41 = left.M41 + right.M41;
		result.M42 = left.M42 + right.M42;
		result.M43 = left.M43 + right.M43;
		result.M44 = left.M44 + right.M44;
		return result;
	}

	Matrix Matrix::operator - (Matrix left, Matrix right)
	{
		Matrix result;
		result.M11 = left.M11 - right.M11;
		result.M12 = left.M12 - right.M12;
		result.M13 = left.M13 - right.M13;
		result.M14 = left.M14 - right.M14;
		result.M21 = left.M21 - right.M21;
		result.M22 = left.M22 - right.M22;
		result.M23 = left.M23 - right.M23;
		result.M24 = left.M24 - right.M24;
		result.M31 = left.M31 - right.M31;
		result.M32 = left.M32 - right.M32;
		result.M33 = left.M33 - right.M33;
		result.M34 = left.M34 - right.M34;
		result.M41 = left.M41 - right.M41;
		result.M42 = left.M42 - right.M42;
		result.M43 = left.M43 - right.M43;
		result.M44 = left.M44 - right.M44;
		return result;
	}

	Matrix Matrix::operator - (Matrix matrix)
	{
		Matrix result;
		result.M11 = -matrix.M11;
		result.M12 = -matrix.M12;
		result.M13 = -matrix.M13;
		result.M14 = -matrix.M14;
		result.M21 = -matrix.M21;
		result.M22 = -matrix.M22;
		result.M23 = -matrix.M23;
		result.M24 = -matrix.M24;
		result.M31 = -matrix.M31;
		result.M32 = -matrix.M32;
		result.M33 = -matrix.M33;
		result.M34 = -matrix.M34;
		result.M41 = -matrix.M41;
		result.M42 = -matrix.M42;
		result.M43 = -matrix.M43;
		result.M44 = -matrix.M44;
		return result;
	}

	bool Matrix::operator == (Matrix left, Matrix right)
	{
		return Matrix::Equals(left, right);
	}

	bool Matrix::operator != (Matrix left, Matrix right)
	{
		return !Matrix::Equals(left, right);
	}

	String^ Matrix::ToString()
	{
		return String::Format(CultureInfo::CurrentCulture, "[[M11:{0} M12:{1} M13:{2} M14:{3}] [M21:{4} M22:{5} M23:{6} M24:{7}] [M31:{8} M32:{9} M33:{10} M34:{11}] [M41:{12} M42:{13} M43:{14} M44:{15}]]",
			M11.ToString(CultureInfo::CurrentCulture), M12.ToString(CultureInfo::CurrentCulture), M13.ToString(CultureInfo::CurrentCulture), M14.ToString(CultureInfo::CurrentCulture),
			M21.ToString(CultureInfo::CurrentCulture), M22.ToString(CultureInfo::CurrentCulture), M23.ToString(CultureInfo::CurrentCulture), M24.ToString(CultureInfo::CurrentCulture),
			M31.ToString(CultureInfo::CurrentCulture), M32.ToString(CultureInfo::CurrentCulture), M33.ToString(CultureInfo::CurrentCulture), M34.ToString(CultureInfo::CurrentCulture),
			M41.ToString(CultureInfo::CurrentCulture), M42.ToString(CultureInfo::CurrentCulture), M43.ToString(CultureInfo::CurrentCulture), M44.ToString(CultureInfo::CurrentCulture));
	}

	int Matrix::GetHashCode()
	{
		return M11.GetHashCode() + M12.GetHashCode() + M13.GetHashCode() + M14.GetHashCode() +
			M21.GetHashCode() + M22.GetHashCode() + M23.GetHashCode() + M24.GetHashCode() +
			M31.GetHashCode() + M32.GetHashCode() + M33.GetHashCode() + M34.GetHashCode() +
			M41.GetHashCode() + M42.GetHashCode() + M43.GetHashCode() + M44.GetHashCode();
	}

	bool Matrix::Equals(Object^ value)
	{
		if (value == nullptr)
			return false;

		if (value->GetType() != GetType())
			return false;

		return Equals(safe_cast<Matrix>(value));
	}

	bool Matrix::Equals(Matrix value)
	{
		return (M11 == value.M11 && M12 == value.M12 && M13 == value.M13 && M14 == value.M14 &&
			M21 == value.M21 && M22 == value.M22 && M23 == value.M23 && M24 == value.M24 &&
			M31 == value.M31 && M32 == value.M32 && M33 == value.M33 && M34 == value.M34 &&
			M41 == value.M41 && M42 == value.M42 && M43 == value.M43 && M44 == value.M44);
	}

	bool Matrix::Equals(Matrix% value1, Matrix% value2)
	{
		return (value1.M11 == value2.M11 && value1.M12 == value2.M12 && value1.M13 == value2.M13 && value1.M14 == value2.M14 &&
			value1.M21 == value2.M21 && value1.M22 == value2.M22 && value1.M23 == value2.M23 && value1.M24 == value2.M24 &&
			value1.M31 == value2.M31 && value1.M32 == value2.M32 && value1.M33 == value2.M33 && value1.M34 == value2.M34 &&
			value1.M41 == value2.M41 && value1.M42 == value2.M42 && value1.M43 == value2.M43 && value1.M44 == value2.M44);
	}
}

#endif
