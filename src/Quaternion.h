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
#pragma once

using System::Runtime::InteropServices::OutAttribute;

namespace BulletSharp
{
	value class Matrix;
	value class Vector3;

	/// <summary>
	/// Defines a four dimensional mathematical quaternion.
	/// </summary>
	/// <unmanaged>D3DXQUATERNION</unmanaged>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class Quaternion : System::IEquatable<Quaternion>
	{
	public:
		/// <summary>
		/// Gets or sets the X component of the quaternion.
		/// </summary>
		/// <value>The X component of the quaternion.</value>
		btScalar X;

		/// <summary>
		/// Gets or sets the Y component of the quaternion.
		/// </summary>
		/// <value>The Y component of the quaternion.</value>
		btScalar Y;

		/// <summary>
		/// Gets or sets the Z component of the quaternion.
		/// </summary>
		/// <value>The Z component of the quaternion.</value>
		btScalar Z;

		/// <summary>
		/// Gets or sets the W component of the quaternion.
		/// </summary>
		/// <value>The W component of the quaternion.</value>
		btScalar W;

		/// <summary>
		/// Initializes a new instance of the <see cref="Quaternion"/> structure.
		/// </summary>
		/// <param name="x">The X component of the quaternion.</param>
		/// <param name="y">The Y component of the quaternion.</param>
		/// <param name="z">The Z component of the quaternion.</param>
		/// <param name="w">The W component of the quaternion.</param>
		Quaternion(btScalar x, btScalar y, btScalar z, btScalar w);

		/// <summary>
		/// Initializes a new instance of the <see cref="Quaternion"/> structure.
		/// </summary>
		/// <param name="value">A <see cref="Vector3"/> containing the first three values of the quaternion.</param>
		/// <param name="w">The W component of the quaternion.</param>
		Quaternion(Vector3 value, btScalar w);

		/// <summary>
		/// Gets the identity <see cref="Quaternion"/> (0, 0, 0, 1).
		/// </summary>
		static property Quaternion Identity { Quaternion get(); }

		/// <summary>
		/// Return the angle of rotation represented by this <see cref="Quaternion"/>.
		/// </summary>
		property btScalar Angle { btScalar get(); }

		/// <summary>
		/// Return the angle of rotation represented by this <see cref="Quaternion"/> along the shortest path.
		/// </summary>
		property btScalar AngleShortestPath { btScalar get(); }

		/// <summary>
		/// Return the axis of rotation represented by this <see cref="Quaternion"/>.
		/// </summary>
		property Vector3 Axis { Vector3 get(); }

		/// <summary>
		/// Gets a value indicating whether this instance is an identity <see cref="Quaternion"/>.
		/// </summary>
		[System::ComponentModel::Browsable(false)]
		property bool IsIdentity { bool get(); }

		/// <summary>
		/// Calculates the length of the quaternion.
		/// </summary>
		/// <returns>The length of the quaternion.</returns>
		property btScalar Length
		{
			btScalar get();
		}

		/// <summary>
		/// Calculates the squared length of the quaternion.
		/// </summary>
		/// <returns>The squared length of the quaternion.</returns>
		property btScalar LengthSquared
		{
			btScalar get();
		}

		/// <summary>
		/// Converts the quaternion into a unit quaternion.
		/// </summary>
		void Normalize();

		/// <summary>
		/// Conjugates the quaternion.
		/// </summary>
		void Conjugate();

		/// <summary>
		/// Conjugates and renormalizes the quaternion.
		/// </summary>
		void Invert();

		/// <summary>
		/// Return the inverse of the quaternion.
		/// </summary>
		/// <returns>The inverse of the quaternion.</returns>
		Quaternion Inverse();

		/// <summary>
		/// Rotate a vector by the quaternion.
		/// </summary>
		/// <param name="v">The vector to rotate.</param>
		/// <returns>The vector rotated by the quaternion.</returns>
		Vector3 Rotate(Vector3 v);

		/// <summary>
		/// Adds two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to add.</param>
		/// <param name="right">The second quaternion to add.</param>
		/// <returns>The sum of the two quaternions.</returns>
		static Quaternion Add(Quaternion left, Quaternion right);

		/// <summary>
		/// Adds two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to add.</param>
		/// <param name="right">The second quaternion to add.</param>
		/// <param name="result">When the method completes, contains the sum of the two quaternions.</param>
		static void Add(Quaternion% left, Quaternion% right, [Out] Quaternion% result);

		/// <summary>
		/// Conjugates a quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to conjugate.</param>
		/// <returns>The conjugated quaternion.</returns>
		static Quaternion Conjugate(Quaternion quaternion);

		/// <summary>
		/// Conjugates a quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to conjugate.</param>
		/// <param name="result">When the method completes, contains the conjugated quaternion.</param>
		static void Conjugate(Quaternion% quaternion, [Out] Quaternion% result);

		/// <summary>
		/// Divides a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to divide.</param>
		/// <param name="right">The second quaternion to divide.</param>
		/// <returns>The divided quaternion.</returns>
		static Quaternion Divide(Quaternion left, Quaternion right);

		/// <summary>
		/// Divides a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to divide.</param>
		/// <param name="right">The second quaternion to divide.</param>
		/// <returns>The divided quaternion.</returns>
		static void Divide(Quaternion% left, Quaternion% right, [Out] Quaternion% result);

		/// <summary>
		/// Calculates the dot product of two quaternions.
		/// </summary>
		/// <param name="left">First source quaternion.</param>
		/// <param name="right">Second source quaternion.</param>
		/// <returns>The dot product of the two quaternions.</returns>
		static btScalar Dot(Quaternion left, Quaternion right);

		/// <summary>
		/// Conjugates and renormalizes the quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to conjugate and renormalize.</param>
		/// <returns>The conjugated and renormalized quaternion.</returns>
		static Quaternion Invert(Quaternion quaternion);

		/// <summary>
		/// Conjugates and renormalizes the quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to conjugate and renormalize.</param>
		/// <param name="result">When the method completes, contains the conjugated and renormalized quaternion.</param>
		static void Invert(Quaternion% quaternion, [Out] Quaternion% result);

		/// <summary>
		/// Performs a linear interpolation between two quaternion.
		/// </summary>
		/// <param name="start">Start quaternion.</param>
		/// <param name="end">End quaternion.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <returns>The linear interpolation of the two quaternions.</returns>
		/// <remarks>
		/// This method performs the linear interpolation based on the following formula.
		/// <code>start + (end - start) * amount</code>
		/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
		/// </remarks>
		static Quaternion Lerp(Quaternion start, Quaternion end, btScalar amount);

		/// <summary>
		/// Performs a linear interpolation between two quaternions.
		/// </summary>
		/// <param name="start">Start quaternion.</param>
		/// <param name="end">End quaternion.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <param name="result">When the method completes, contains the linear interpolation of the two quaternions.</param>
		/// <remarks>
		/// This method performs the linear interpolation based on the following formula.
		/// <code>start + (end - start) * amount</code>
		/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
		/// </remarks>
		static void Lerp(Quaternion% start, Quaternion% end, btScalar amount, [Out] Quaternion% result);

		/// <summary>
		/// Modulates a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to modulate.</param>
		/// <param name="right">The second quaternion to modulate.</param>
		/// <returns>The modulated quaternion.</returns>
		static Quaternion Multiply(Quaternion left, Quaternion right);

		/// <summary>
		/// Modulates a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to modulate.</param>
		/// <param name="right">The second quaternion to modulate.</param>
		/// <param name="result">When the moethod completes, contains the modulated quaternion.</param>
		static void Multiply(Quaternion% left, Quaternion% right, [Out] Quaternion% result);

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion Multiply(Quaternion quaternion, btScalar scale);

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <param name="result">When the method completes, contains the scaled quaternion.</param>
		static void Multiply(Quaternion% quaternion, btScalar scale, [Out] Quaternion% result);

		/// <summary>
		/// Reverses the direction of a given quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to negate.</param>
		/// <returns>A quaternion facing in the opposite direction.</returns>
		static Quaternion Negate(Quaternion quaternion);

		/// <summary>
		/// Reverses the direction of a given quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to negate.</param>
		/// <param name="result">When the method completes, contains a quaternion facing in the opposite direction.</param>
		static void Negate(Quaternion% quaternion, [Out] Quaternion% result);

		/// <summary>
		/// Converts the quaternion into a unit quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to normalize.</param>
		/// <returns>The normalized quaternion.</returns>
		static Quaternion Normalize(Quaternion quaternion);

		/// <summary>
		/// Converts the quaternion into a unit quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to normalize.</param>
		/// <param name="result">When the method completes, contains the normalized quaternion.</param>
		static void Normalize(Quaternion% quaternion, [Out] Quaternion% result);

		/// <summary>
		/// Creates a quaternion given a rotation and an axis.
		/// </summary>
		/// <param name="axis">The axis of rotation.</param>
		/// <param name="angle">The angle of rotation.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationAxis(Vector3 axis, btScalar angle);

		/// <summary>
		/// Creates a quaternion given a rotation and an axis.
		/// </summary>
		/// <param name="axis">The axis of rotation.</param>
		/// <param name="angle">The angle of rotation.</param>
		/// <param name="result">When the method completes, contains the newly created quaternion.</param>
		static void RotationAxis(Vector3% axis, btScalar angle, [Out] Quaternion% result);

		/// <summary>
		/// Creates a quaternion given a rotation matrix.
		/// </summary>
		/// <param name="matrix">The rotation matrix.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationMatrix(Matrix matrix);

		/// <summary>
		/// Creates a quaternion given a rotation matrix.
		/// </summary>
		/// <param name="matrix">The rotation matrix.</param>
		/// <param name="result">When the method completes, contains the newly created quaternion.</param>
		static void RotationMatrix(Matrix% matrix, [Out] Quaternion% result);

		/// <summary>
		/// Creates a quaternion given a yaw, pitch, and roll value.
		/// </summary>
		/// <param name="yaw">The yaw of rotation.</param>
		/// <param name="pitch">The pitch of rotation.</param>
		/// <param name="roll">The roll of rotation.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationYawPitchRoll(btScalar yaw, btScalar pitch, btScalar roll);

		/// <summary>
		/// Creates a quaternion given a yaw, pitch, and roll value.
		/// </summary>
		/// <param name="yaw">The yaw of rotation.</param>
		/// <param name="pitch">The pitch of rotation.</param>
		/// <param name="roll">The roll of rotation.</param>
		/// <param name="result">When the method completes, contains the newly created quaternion.</param>
		static void RotationYawPitchRoll(btScalar yaw, btScalar pitch, btScalar roll, [Out] Quaternion% result);

		/// <summary>
		/// Interpolates between two quaternions, using spherical linear interpolation.
		/// </summary>
		/// <param name="start">Start quaternion.</param>
		/// <param name="end">End quaternion.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <returns>The spherical linear interpolation of the two quaternions.</returns>
		static Quaternion Slerp(Quaternion start, Quaternion end, btScalar amount);

		/// <summary>
		/// Interpolates between two quaternions, using spherical linear interpolation.
		/// </summary>
		/// <param name="start">Start quaternion.</param>
		/// <param name="end">End quaternion.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <param name="result">When the method completes, contains the spherical linear interpolation of the two quaternions.</param>
		static void Slerp(Quaternion% start, Quaternion% end, btScalar amount, [Out] Quaternion% result);

		/// <summary>
		/// Subtracts two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to subtract.</param>
		/// <param name="right">The second quaternion to subtract.</param>
		/// <returns>The difference of the two quaternions.</returns>
		static Quaternion Subtract(Quaternion left, Quaternion right);

		/// <summary>
		/// Subtracts two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to subtract.</param>
		/// <param name="right">The second quaternion to subtract.</param>
		/// <param name="result">When the method completes, contains the difference of the two quaternions.</param>
		static void Subtract(Quaternion% left, Quaternion% right, [Out] Quaternion% result);

		/// <summary>
		/// Multiplies a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to multiply.</param>
		/// <param name="right">The second quaternion to multiply.</param>
		/// <returns>The multiplied quaternion.</returns>
		static Quaternion operator * (Quaternion left, Quaternion right);

		/// <summary>
		/// Multiplies a quaternion by a vector.
		/// </summary>
		/// <param name="left">The quaternion to multiply.</param>
		/// <param name="right">The vector to multiply by.</param>
		/// <returns>The multiplied quaternion.</returns>
		static Quaternion operator * (Quaternion left, Vector3 right);

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion operator * (Quaternion quaternion, btScalar scale);

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion operator * (btScalar scale, Quaternion quaternion);

		/// <summary>
		/// Divides a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to divide.</param>
		/// <param name="right">The second quaternion to divide.</param>
		/// <returns>The divided quaternion.</returns>
		static Quaternion operator / (Quaternion left, btScalar right);

		/// <summary>
		/// Adds two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to add.</param>
		/// <param name="right">The second quaternion to add.</param>
		/// <returns>The sum of the two quaternions.</returns>
		static Quaternion operator + (Quaternion left, Quaternion right);

		/// <summary>
		/// Subtracts two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to subtract.</param>
		/// <param name="right">The second quaternion to subtract.</param>
		/// <returns>The difference of the two quaternions.</returns>
		static Quaternion operator - (Quaternion left, Quaternion right);

		/// <summary>
		/// Reverses the direction of a given quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to negate.</param>
		/// <returns>A quaternion facing in the opposite direction.</returns>
		static Quaternion operator - (Quaternion quaternion);

		/// <summary>
		/// Tests for equality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator == (Quaternion left, Quaternion right);

		/// <summary>
		/// Tests for inequality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator != (Quaternion left, Quaternion right);

		/// <summary>
		/// Converts the value of the object to its equivalent string representation.
		/// </summary>
		/// <returns>The string representation of the value of this instance.</returns>
		virtual System::String^ ToString() override;

		/// <summary>
		/// Returns the hash code for this instance.
		/// </summary>
		/// <returns>A 32-bit signed integer hash code.</returns>
		virtual int GetHashCode() override;

		/// <summary>
		/// Returns a value that indicates whether the current instance is equal to a specified object. 
		/// </summary>
		/// <param name="obj">Object to make the comparison with.</param>
		/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
		virtual bool Equals(System::Object^ obj) override;

		/// <summary>
		/// Returns a value that indicates whether the current instance is equal to the specified object. 
		/// </summary>
		/// <param name="other">Object to make the comparison with.</param>
		/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
		virtual bool Equals(Quaternion other);

		/// <summary>
		/// Determines whether the specified object instances are considered equal. 
		/// </summary>
		/// <param name="value1"></param>
		/// <param name="value2"></param>
		/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
		/// if both are <c>null</c> references or if <c>value1.Equals(value2)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
		static bool Equals(Quaternion% value1, Quaternion% value2);
	};
}
