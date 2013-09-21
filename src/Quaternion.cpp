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

#ifdef GRAPHICS_NONE

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector3.h"

using namespace System;
using namespace System::Globalization;

namespace BulletSharp
{
	Quaternion::Quaternion(btScalar x, btScalar y, btScalar z, btScalar w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Quaternion::Quaternion( Vector3 value, btScalar w )
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = w;
	}

	Quaternion Quaternion::Identity::get()
	{
		Quaternion result;
		result.X = 0.0f;
		result.Y = 0.0f;
		result.Z = 0.0f;
		result.W = 1.0f;
		return result;
	}

	btScalar Quaternion::Angle::get()
	{
		return 2.0f * System::Math::Acos(W);
	}

	btScalar Quaternion::AngleShortestPath::get()
	{
		btScalar dot = (X * X) + (Y * Y) + (Z * Z) + (W * W);
		if (dot < 0) {
			return 2.0f * System::Math::Acos(W);
		} else {
			return 2.0f * System::Math::Acos(-W);
		}
	}

	Vector3 Quaternion::Axis::get()
	{
		btScalar sSquared = 1.0f - W * W;

        if (sSquared < btScalar(10.0) * SIMD_EPSILON) //Check for divide by zero
			return Vector3(1.0, 0.0, 0.0);  // Arbitrary
        btScalar s = 1.0f / btSqrt(sSquared);
        return Vector3(X * s, Y * s, Z * s);
	}

	bool Quaternion::IsIdentity::get()
	{
		if( X != 0.0f || Y != 0.0f || Z != 0.0f )
			return false;

		return (W == 1.0f);
	}

	btScalar Quaternion::Length()
	{
		return static_cast<btScalar>( System::Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) ) );
	}
	
	btScalar Quaternion::LengthSquared()
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	void Quaternion::Normalize()
	{
		btScalar length = 1.0f / Length();
		X *= length;
		Y *= length;
		Z *= length;
		W *= length;
	}

	void Quaternion::Conjugate()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}

	void Quaternion::Invert()
	{
		btScalar lengthSq = 1.0f / ( (X * X) + (Y * Y) + (Z * Z) + (W * W) );
		X = -X * lengthSq;
		Y = -Y * lengthSq;
		Z = -Z * lengthSq;
		W = W * lengthSq;
	}

	Quaternion Quaternion::Add( Quaternion left, Quaternion right )
	{
		Quaternion result;
		result.X = left.X + right.X;
		result.Y = left.Y + right.Y;
		result.Z = left.Z + right.Z;
		result.W = left.W + right.W;
		return result;
	}

	void Quaternion::Add( Quaternion% left, Quaternion% right, [Out] Quaternion% result )
	{
		Quaternion r;
		r.X = left.X + right.X;
		r.Y = left.Y + right.Y;
		r.Z = left.Z + right.Z;
		r.W = left.W + right.W;

		result = r;
	}

	Quaternion Quaternion::Conjugate( Quaternion quat )
	{
		Quaternion result;
		result.X = -quat.X;
		result.Y = -quat.Y;
		result.Z = -quat.Z;
		result.W = quat.W;
		return result;
	}

	void Quaternion::Conjugate( Quaternion% quat, [Out] Quaternion% result )
	{
		result.X = -quat.X;
		result.Y = -quat.Y;
		result.Z = -quat.Z;
		result.W = quat.W;
	}

	Quaternion Quaternion::Divide( Quaternion left, Quaternion right )
	{
		Quaternion result;
		result.X = left.X / right.X;
		result.Y = left.Y / right.Y;
		result.Z = left.Z / right.Z;
		result.W = left.W / right.W;
		return result;
	}

	void Quaternion::Divide( Quaternion% left, Quaternion% right, [Out] Quaternion% result )
	{
		result.X = left.X / right.X;
		result.Y = left.Y / right.Y;
		result.Z = left.Z / right.Z;
		result.W = left.W / right.W;
	}
	
	btScalar Quaternion::Dot( Quaternion left, Quaternion right )
	{
		return (left.X * right.X) + (left.Y * right.Y) + (left.Z * right.Z) + (left.W * right.W); 
	}

	Quaternion Quaternion::Invert( Quaternion quaternion )
	{
		Quaternion result;
		btScalar lengthSq = 1.0f / ( (quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W) );

		result.X = -quaternion.X * lengthSq;
		result.Y = -quaternion.Y * lengthSq;
		result.Z = -quaternion.Z * lengthSq;
		result.W = quaternion.W * lengthSq;

		return result;
	}

	void Quaternion::Invert( Quaternion% quaternion, [Out] Quaternion% result )
	{
		btScalar lengthSq = 1.0f / ( (quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W) );

		result.X = -quaternion.X * lengthSq;
		result.Y = -quaternion.Y * lengthSq;
		result.Z = -quaternion.Z * lengthSq;
		result.W = quaternion.W * lengthSq;
	}

	Quaternion Quaternion::Lerp( Quaternion left, Quaternion right, btScalar amount )
	{
		Quaternion result;
		btScalar inverse = 1.0f - amount;
		btScalar dot = (left.X * right.X) + (left.Y * right.Y) + (left.Z * right.Z) + (left.W * right.W);

		if( dot >= 0.0f )
		{
			result.X = (inverse * left.X) + (amount * right.X);
			result.Y = (inverse * left.Y) + (amount * right.Y);
			result.Z = (inverse * left.Z) + (amount * right.Z);
			result.W = (inverse * left.W) + (amount * right.W);
		}
		else
		{
			result.X = (inverse * left.X) - (amount * right.X);
			result.Y = (inverse * left.Y) - (amount * right.Y);
			result.Z = (inverse * left.Z) - (amount * right.Z);
			result.W = (inverse * left.W) - (amount * right.W);
		}

		btScalar invLength = 1.0f / result.Length();

		result.X *= invLength;
		result.Y *= invLength;
		result.Z *= invLength;
		result.W *= invLength;

		return result;
	}

	void Quaternion::Lerp( Quaternion% left, Quaternion% right, btScalar amount, [Out] Quaternion% result )
	{
		btScalar inverse = 1.0f - amount;
		btScalar dot = (left.X * right.X) + (left.Y * right.Y) + (left.Z * right.Z) + (left.W * right.W); 

		if( dot >= 0.0f )
		{
			result.X = (inverse * left.X) + (amount * right.X);
			result.Y = (inverse * left.Y) + (amount * right.Y);
			result.Z = (inverse * left.Z) + (amount * right.Z);
			result.W = (inverse * left.W) + (amount * right.W);
		}
		else
		{
			result.X = (inverse * left.X) - (amount * right.X);
			result.Y = (inverse * left.Y) - (amount * right.Y);
			result.Z = (inverse * left.Z) - (amount * right.Z);
			result.W = (inverse * left.W) - (amount * right.W);
		}

		btScalar invLength = 1.0f / result.Length();

		result.X *= invLength;
		result.Y *= invLength;
		result.Z *= invLength;
		result.W *= invLength;
	}

	Quaternion Quaternion::Multiply( Quaternion left, Quaternion right )
	{
		Quaternion quaternion;
		btScalar lx = left.X;
		btScalar ly = left.Y;
		btScalar lz = left.Z;
		btScalar lw = left.W;
		btScalar rx = right.X;
		btScalar ry = right.Y;
		btScalar rz = right.Z;
		btScalar rw = right.W;

		quaternion.X = (lx * rw + rx * lw) + (ly * rz) - (lz * ry);
		quaternion.Y = (ly * rw + ry * lw) + (lz * rx) - (lx * rz);
		quaternion.Z = (lz * rw + rz * lw) + (lx * ry) - (ly * rx);
		quaternion.W = (lw * rw) - (lx * rx + ly * ry + lz * rz);

		return quaternion;
	}

	void Quaternion::Multiply( Quaternion% left, Quaternion% right, [Out] Quaternion% result )
	{
		btScalar lx = left.X;
		btScalar ly = left.Y;
		btScalar lz = left.Z;
		btScalar lw = left.W;
		btScalar rx = right.X;
		btScalar ry = right.Y;
		btScalar rz = right.Z;
		btScalar rw = right.W;

		result.X = (lx * rw + rx * lw) + (ly * rz) - (lz * ry);
		result.Y = (ly * rw + ry * lw) + (lz * rx) - (lx * rz);
		result.Z = (lz * rw + rz * lw) + (lx * ry) - (ly * rx);
		result.W = (lw * rw) - (lx * rx + ly * ry + lz * rz);
	}

	Quaternion Quaternion::Multiply( Quaternion quaternion, btScalar scale )
	{
		Quaternion result;
		result.X = quaternion.X * scale;
		result.Y = quaternion.Y * scale;
		result.Z = quaternion.Z * scale;
		result.W = quaternion.W * scale;
		return result;
	}

	void Quaternion::Multiply( Quaternion% quaternion, btScalar scale, [Out] Quaternion% result )
	{
		result.X = quaternion.X * scale;
		result.Y = quaternion.Y * scale;
		result.Z = quaternion.Z * scale;
		result.W = quaternion.W * scale;
	}

	Quaternion Quaternion::Negate( Quaternion quat )
	{
		Quaternion result;
		result.X = -quat.X;
		result.Y = -quat.Y;
		result.Z = -quat.Z;
		result.W = -quat.W;
		return result;
	}

	void Quaternion::Negate( Quaternion% quat, [Out] Quaternion% result )
	{
		result.X = -quat.X;
		result.Y = -quat.Y;
		result.Z = -quat.Z;
		result.W = -quat.W;
	}

	Quaternion Quaternion::Normalize( Quaternion quat )
	{
		quat.Normalize();
		return quat;
	}

	void Quaternion::Normalize( Quaternion% quat, [Out] Quaternion% result )
	{
		btScalar length = 1.0f / quat.Length();
		result.X = quat.X * length;
		result.Y = quat.Y * length;
		result.Z = quat.Z * length;
		result.W = quat.W * length;
	}

	Quaternion Quaternion::RotationAxis( Vector3 axis, btScalar angle )
	{
		Quaternion result;

		Vector3::Normalize( axis, axis );

		btScalar half = angle * 0.5f;
		btScalar sin = static_cast<btScalar>( System::Math::Sin( static_cast<double>( half ) ) );
		btScalar cos = static_cast<btScalar>( System::Math::Cos( static_cast<double>( half ) ) );

		result.X = axis.X * sin;
		result.Y = axis.Y * sin;
		result.Z = axis.Z * sin;
		result.W = cos;

		return result;
	}

	void Quaternion::RotationAxis( Vector3% axis, btScalar angle, [Out] Quaternion% result )
	{
		Vector3::Normalize( axis, axis );

		btScalar half = angle * 0.5f;
		btScalar sin = static_cast<btScalar>( System::Math::Sin( static_cast<double>( half ) ) );
		btScalar cos = static_cast<btScalar>( System::Math::Cos( static_cast<double>( half ) ) );

		result.X = axis.X * sin;
		result.Y = axis.Y * sin;
		result.Z = axis.Z * sin;
		result.W = cos;
	}
	
	Quaternion Quaternion::RotationMatrix( Matrix matrix )
	{
		Quaternion result;
		btScalar scale = matrix.M11 + matrix.M22 + matrix.M33;

		if( scale > 0.0f )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(scale + 1.0f) ) );

			result.W = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			result.X = (matrix.M23 - matrix.M32) * sqrt;
			result.Y = (matrix.M31 - matrix.M13) * sqrt;
			result.Z = (matrix.M12 - matrix.M21) * sqrt;

			return result;
		}

		if( (matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33) )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M11 - matrix.M22 - matrix.M33) ) );
			btScalar half = 0.5f / sqrt;

			result.X = 0.5f * sqrt;
			result.Y = (matrix.M12 + matrix.M21) * half;
			result.Z = (matrix.M13 + matrix.M31) * half;
			result.W = (matrix.M23 - matrix.M32) * half;

			return result;
		}

		if( matrix.M22 > matrix.M33 )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M22 - matrix.M11 - matrix.M33) ) );
			btScalar half = 0.5f / sqrt;

			result.X = (matrix.M21 + matrix.M12) * half;
			result.Y = 0.5f * sqrt;
			result.Z = (matrix.M32 + matrix.M23) * half;
			result.W = (matrix.M31 - matrix.M13) * half;

			return result;
		}

		btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M33 - matrix.M11 - matrix.M22) ) );
		btScalar half = 0.5f / sqrt;

		result.X = (matrix.M31 + matrix.M13) * half;
		result.Y = (matrix.M32 + matrix.M23) * half;
		result.Z = 0.5f * sqrt;
		result.W = (matrix.M12 - matrix.M21) * half;

		return result;
	}

	void Quaternion::RotationMatrix( Matrix% matrix, [Out] Quaternion% result )
	{
		btScalar scale = matrix.M11 + matrix.M22 + matrix.M33;

		if( scale > 0.0f )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(scale + 1.0f) ) );

			result.W = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			result.X = (matrix.M23 - matrix.M32) * sqrt;
			result.Y = (matrix.M31 - matrix.M13) * sqrt;
			result.Z = (matrix.M12 - matrix.M21) * sqrt;
			return;
		}

		if( (matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33) )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M11 - matrix.M22 - matrix.M33) ) );
			btScalar half = 0.5f / sqrt;

			result.X = 0.5f * sqrt;
			result.Y = (matrix.M12 + matrix.M21) * half;
			result.Z = (matrix.M13 + matrix.M31) * half;
			result.W = (matrix.M23 - matrix.M32) * half;
			return;
		}

		if( matrix.M22 > matrix.M33 )
		{
			btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M22 - matrix.M11 - matrix.M33) ) );
			btScalar half = 0.5f / sqrt;

			result.X = (matrix.M21 + matrix.M12) * half;
			result.Y = 0.5f * sqrt;
			result.Z = (matrix.M32 + matrix.M23) * half;
			result.W = (matrix.M31 - matrix.M13) * half;
			return;
		}

		btScalar sqrt = static_cast<btScalar>( System::Math::Sqrt( static_cast<double>(1.0f + matrix.M33 - matrix.M11 - matrix.M22) ) );
		btScalar half = 0.5f / sqrt;

		result.X = (matrix.M31 + matrix.M13) * half;
		result.Y = (matrix.M32 + matrix.M23) * half;
		result.Z = 0.5f * sqrt;
		result.W = (matrix.M12 - matrix.M21) * half;
	}

	Quaternion Quaternion::RotationYawPitchRoll( btScalar yaw, btScalar pitch, btScalar roll )
	{
		Quaternion result;

		btScalar halfRoll = roll * 0.5f;
		btScalar sinRoll = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfRoll ) ) );
		btScalar cosRoll = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfRoll ) ) );
		btScalar halfPitch = pitch * 0.5f;
		btScalar sinPitch = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfPitch ) ) );
		btScalar cosPitch = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfPitch ) ) );
		btScalar halfYaw = yaw * 0.5f;
		btScalar sinYaw = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfYaw ) ) );
		btScalar cosYaw = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfYaw ) ) );

		result.X = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
		result.Y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
		result.Z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
		result.W = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);

		return result;
	}

	void Quaternion::RotationYawPitchRoll( btScalar yaw, btScalar pitch, btScalar roll, [Out] Quaternion% result )
	{
		btScalar halfRoll = roll * 0.5f;
		btScalar sinRoll = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfRoll ) ) );
		btScalar cosRoll = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfRoll ) ) );
		btScalar halfPitch = pitch * 0.5f;
		btScalar sinPitch = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfPitch ) ) );
		btScalar cosPitch = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfPitch ) ) );
		btScalar halfYaw = yaw * 0.5f;
		btScalar sinYaw = static_cast<btScalar>( System::Math::Sin( static_cast<double>( halfYaw ) ) );
		btScalar cosYaw = static_cast<btScalar>( System::Math::Cos( static_cast<double>( halfYaw ) ) );

		result.X = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
		result.Y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
		result.Z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
		result.W = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
	}

	Quaternion Quaternion::Slerp( Quaternion q1, Quaternion q2, btScalar t )
	{
		Quaternion result;

		btScalar opposite;
		btScalar inverse;
		btScalar dot = (q1.X * q2.X) + (q1.Y * q2.Y) + (q1.Z * q2.Z) + (q1.W * q2.W);
		bool flag = false;

		if( dot < 0.0f )
		{
			flag = true;
			dot = -dot;
		}

		if( dot > 0.999999f )
		{
			inverse = 1.0f - t;
			opposite = flag ? -t : t;
		}
		else
		{
			btScalar acos = static_cast<btScalar>( System::Math::Acos( static_cast<double>( dot ) ) );
			btScalar invSin = static_cast<btScalar>( ( 1.0f / System::Math::Sin( static_cast<double>( acos ) ) ) );

			inverse = ( static_cast<btScalar>( System::Math::Sin( static_cast<double>( (1.0f - t) * acos ) ) ) ) * invSin;
			opposite = flag ? ( ( static_cast<btScalar>( -System::Math::Sin( static_cast<double>( t * acos ) ) ) ) * invSin ) : ( ( static_cast<btScalar>( System::Math::Sin( static_cast<double>( t * acos ) ) ) ) * invSin );
		}

		result.X = (inverse * q1.X) + (opposite * q2.X);
		result.Y = (inverse * q1.Y) + (opposite * q2.Y);
		result.Z = (inverse * q1.Z) + (opposite * q2.Z);
		result.W = (inverse * q1.W) + (opposite * q2.W);

		return result;
	}

	void Quaternion::Slerp( Quaternion% q1, Quaternion% q2, btScalar t, [Out] Quaternion% result )
	{
		btScalar opposite;
		btScalar inverse;
		btScalar dot = (q1.X * q2.X) + (q1.Y * q2.Y) + (q1.Z * q2.Z) + (q1.W * q2.W);
		bool flag = false;

		if( dot < 0.0f )
		{
			flag = true;
			dot = -dot;
		}

		if( dot > 0.999999f )
		{
			inverse = 1.0f - t;
			opposite = flag ? -t : t;
		}
		else
		{
			btScalar acos = static_cast<btScalar>( System::Math::Acos( static_cast<double>( dot ) ) );
			btScalar invSin = static_cast<btScalar>( ( 1.0f / System::Math::Sin( static_cast<double>( acos ) ) ) );

			inverse = ( static_cast<btScalar>( System::Math::Sin( static_cast<double>( (1.0f - t) * acos ) ) ) ) * invSin;
			opposite = flag ? ( ( static_cast<btScalar>( -System::Math::Sin( static_cast<double>( t * acos ) ) ) ) * invSin ) : ( ( static_cast<btScalar>( System::Math::Sin( static_cast<double>( t * acos ) ) ) ) * invSin );
		}

		result.X = (inverse * q1.X) + (opposite * q2.X);
		result.Y = (inverse * q1.Y) + (opposite * q2.Y);
		result.Z = (inverse * q1.Z) + (opposite * q2.Z);
		result.W = (inverse * q1.W) + (opposite * q2.W);
	}

	Quaternion Quaternion::Subtract( Quaternion left, Quaternion right )
	{
		Quaternion result;
		result.X = left.X - right.X;
		result.Y = left.Y - right.Y;
		result.Z = left.Z - right.Z;
		result.W = left.W - right.W;
		return result;
	}

	void Quaternion::Subtract( Quaternion% left, Quaternion% right, [Out] Quaternion% result )
	{
		result.X = left.X - right.X;
		result.Y = left.Y - right.Y;
		result.Z = left.Z - right.Z;
		result.W = left.W - right.W;
	}

	Quaternion Quaternion::operator * (Quaternion left, Quaternion right)
	{
		Quaternion quaternion;
		btScalar lx = left.X;
		btScalar ly = left.Y;
		btScalar lz = left.Z;
		btScalar lw = left.W;
		btScalar rx = right.X;
		btScalar ry = right.Y;
		btScalar rz = right.Z;
		btScalar rw = right.W;

		quaternion.X = (lx * rw + rx * lw) + (ly * rz) - (lz * ry);
		quaternion.Y = (ly * rw + ry * lw) + (lz * rx) - (lx * rz);
		quaternion.Z = (lz * rw + rz * lw) + (lx * ry) - (ly * rx);
		quaternion.W = (lw * rw) - (lx * rx + ly * ry + lz * rz);

		return quaternion;
	}

	Quaternion Quaternion::operator * (Quaternion quaternion, btScalar scale)
	{
		Quaternion result;
		result.X = quaternion.X * scale;
		result.Y = quaternion.Y * scale;
		result.Z = quaternion.Z * scale;
		result.W = quaternion.W * scale;
		return result;
	}

	Quaternion Quaternion::operator * (btScalar scale, Quaternion quaternion)
	{
		Quaternion result;
		result.X = quaternion.X * scale;
		result.Y = quaternion.Y * scale;
		result.Z = quaternion.Z * scale;
		result.W = quaternion.W * scale;
		return result;
	}

	Quaternion Quaternion::operator / (Quaternion lhs, btScalar rhs)
	{
		Quaternion result;
		result.X = lhs.X / rhs;
		result.Y = lhs.Y / rhs;
		result.Z = lhs.Z / rhs;
		result.W = lhs.W / rhs;
		return result;
	}

	Quaternion Quaternion::operator + (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		result.X = lhs.X + rhs.X;
		result.Y = lhs.Y + rhs.Y;
		result.Z = lhs.Z + rhs.Z;
		result.W = lhs.W + rhs.W;
		return result;
	}

	Quaternion Quaternion::operator - (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		result.X = lhs.X - rhs.X;
		result.Y = lhs.Y - rhs.Y;
		result.Z = lhs.Z - rhs.Z;
		result.W = lhs.W - rhs.W;
		return result;
	}

	Quaternion Quaternion::operator - (Quaternion quaternion)
	{
		Quaternion result;
		result.X = -quaternion.X;
		result.Y = -quaternion.Y;
		result.Z = -quaternion.Z;
		result.W = -quaternion.W;
		return result;
	}

	bool Quaternion::operator == ( Quaternion left, Quaternion right )
	{
		return Quaternion::Equals( left, right );
	}

	bool Quaternion::operator != ( Quaternion left, Quaternion right )
	{
		return !Quaternion::Equals( left, right );
	}

	String^ Quaternion::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "X:{0} Y:{1} Z:{2} W:{3}", X.ToString(CultureInfo::CurrentCulture), 
			Y.ToString(CultureInfo::CurrentCulture), Z.ToString(CultureInfo::CurrentCulture),
			W.ToString(CultureInfo::CurrentCulture) );
	}

	int Quaternion::GetHashCode()
	{
		return X.GetHashCode() + Y.GetHashCode() + Z.GetHashCode() + W.GetHashCode();
	}

	bool Quaternion::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<Quaternion>( value ) );
	}

	bool Quaternion::Equals( Quaternion value )
	{
		return ( X == value.X && Y == value.Y && Z == value.Z && W == value.W );
	}

	bool Quaternion::Equals( Quaternion% value1, Quaternion% value2 )
	{
		return ( value1.X == value2.X && value1.Y == value2.Y && value1.Z == value2.Z && value1.W == value2.W );
	}
}

#endif
