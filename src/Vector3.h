/*
* Copyright (c) 2007-2010 SlimDX Group
* Adapted for BulletSharp by Andres Traks
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

#include "Vector4.h"

using System::Runtime::InteropServices::OutAttribute;

namespace BulletSharp
{
	value class Matrix;

	/// <summary>
	/// Defines a three component vector.
	/// </summary>
	/// <unmanaged>D3DXVECTOR3</unmanaged>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
	public value class Vector3 : System::IEquatable<Vector3>
	{
	public:
		/// <summary>
		/// Gets or sets the X component of the vector.
		/// </summary>
		/// <value>The X component of the vector.</value>
		btScalar X;

		/// <summary>
		/// Gets or sets the Y component of the vector.
		/// </summary>
		/// <value>The Y component of the vector.</value>
		btScalar Y;

		/// <summary>
		/// Gets or sets the Z component of the vector.
		/// </summary>
		/// <value>The Z component of the vector.</value>
		btScalar Z;

		property btScalar default[int]
		{
			btScalar get(int index);
		void set(int index, btScalar value);
		}
			/// <summary>
			/// Gets a <see cref="Vector3"/> with all of its components set to zero.
			/// </summary>
			/// <value>A <see cref="Vector3"/> that has all of its components set to zero.</value>
		static property Vector3 Zero { Vector3 get() { return Vector3(0, 0, 0); } }

		/// <summary>
		/// Gets the X unit <see cref="Vector3"/> (1, 0, 0).
		/// </summary>
		/// <value>A <see cref="Vector3"/> that has a value of (1, 0, 0).</value>
		static property Vector3 UnitX { Vector3 get() { return Vector3(1, 0, 0); } }

		/// <summary>
		/// Gets the Y unit <see cref="Vector3"/> (0, 1, 0).
		/// </summary>
		/// <value>A <see cref="Vector3"/> that has a value of (0, 1, 0).</value>
		static property Vector3 UnitY { Vector3 get() { return Vector3(0, 1, 0); } }

		/// <summary>
		/// Gets the Z unit <see cref="Vector3"/> (0, 0, 1).
		/// </summary>
		/// <value>A <see cref="Vector3"/> that has a value of (0, 0, 1).</value>
		static property Vector3 UnitZ { Vector3 get() { return Vector3(0, 0, 1); } }

		/// <summary>
		/// Gets the size of the <see cref="Vector3"/> type, in bytes.
		/// </summary>
		static property int SizeInBytes { int get() { return System::Runtime::InteropServices::Marshal::SizeOf(Vector3::typeid); } }

		/// <summary>
		/// Initializes a new instance of the <see cref="Vector3"/> class.
		/// </summary>
		/// <param name="value">The value that will be assigned to all components.</param>
		Vector3(btScalar value);

		/// <summary>
		/// Initializes a new instance of the <see cref="Vector3"/> class.
		/// </summary>
		/// <param name="x">Initial value for the X component of the vector.</param>
		/// <param name="y">Initial value for the Y component of the vector.</param>
		/// <param name="z">Initial value for the Z component of the vector.</param>
		Vector3(btScalar x, btScalar y, btScalar z);

		/// <summary>
		/// Adds two vectors.
		/// </summary>
		/// <param name="left">The first vector to add.</param>
		/// <param name="right">The second vector to add.</param>
		/// <returns>The sum of the two vectors.</returns>
		static Vector3 Add(Vector3 left, Vector3 right);

		/// <summary>
		/// Adds two vectors.
		/// </summary>
		/// <param name="left">The first vector to add.</param>
		/// <param name="right">The second vector to add.</param>
		/// <param name="result">When the method completes, contains the sum of the two vectors.</param>
		static void Add(Vector3% left, Vector3% right, [Out] Vector3% result);

		btScalar Angle(Vector3 v);

		/// <summary>
		/// Returns a <see cref="Vector3"/> containing the 3D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 3D triangle.
		/// </summary>
		/// <param name="value1">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 1 of the triangle.</param>
		/// <param name="value2">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 2 of the triangle.</param>
		/// <param name="value3">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 3 of the triangle.</param>
		/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
		/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
		/// <returns>A new <see cref="Vector3"/> containing the 3D Cartesian coordinates of the specified point.</returns>
		static Vector3 Barycentric(Vector3 value1, Vector3 value2, Vector3 value3, btScalar amount1, btScalar amount2);

		/// <summary>
		/// Returns a <see cref="Vector3"/> containing the 3D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 3D triangle.
		/// </summary>
		/// <param name="value1">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 1 of the triangle.</param>
		/// <param name="value2">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 2 of the triangle.</param>
		/// <param name="value3">A <see cref="Vector3"/> containing the 3D Cartesian coordinates of vertex 3 of the triangle.</param>
		/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
		/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
		/// <param name="result">When the method completes, contains the 3D Cartesian coordinates of the specified point.</param>
		static void Barycentric(Vector3% value1, Vector3% value2, Vector3% value3, btScalar amount1, btScalar amount2, [Out] Vector3% result);

		/// <summary>
		/// Performs a Catmull-Rom interpolation using the specified positions.
		/// </summary>
		/// <param name="value1">The first position in the interpolation.</param>
		/// <param name="value2">The second position in the interpolation.</param>
		/// <param name="value3">The third position in the interpolation.</param>
		/// <param name="value4">The fourth position in the interpolation.</param>
		/// <param name="amount">Weighting factor.</param>
		/// <returns>A vector that is the result of the Catmull-Rom interpolation.</returns>
		static Vector3 CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, btScalar amount);

		/// <summary>
		/// Performs a Catmull-Rom interpolation using the specified positions.
		/// </summary>
		/// <param name="value1">The first position in the interpolation.</param>
		/// <param name="value2">The second position in the interpolation.</param>
		/// <param name="value3">The third position in the interpolation.</param>
		/// <param name="value4">The fourth position in the interpolation.</param>
		/// <param name="amount">Weighting factor.</param>
		/// <param name="result">When the method completes, contains the result of the Catmull-Rom interpolation.</param>
		static void CatmullRom(Vector3% value1, Vector3% value2, Vector3% value3, Vector3% value4, btScalar amount, [Out] Vector3% result);

		/// <summary>
		/// Restricts a value to be within a specified range.
		/// </summary>
		/// <param name="value">The value to clamp.</param>
		/// <param name="min">The minimum value.</param>
		/// <param name="max">The maximum value.</param>
		/// <returns>The clamped value.</returns>
		static Vector3 Clamp(Vector3 value, Vector3 min, Vector3 max);

		/// <summary>
		/// Restricts a value to be within a specified range.
		/// </summary>
		/// <param name="value">The value to clamp.</param>
		/// <param name="min">The minimum value.</param>
		/// <param name="max">The maximum value.</param>
		/// <param name="result">When the method completes, contains the clamped value.</param>
		static void Clamp(Vector3% value, Vector3% min, Vector3% max, [Out] Vector3% result);

		Vector3 Cross(Vector3 v);

		/// <summary>
		/// Calculates the cross product of two vectors.
		/// </summary>
		/// <param name="left">First source vector.</param>
		/// <param name="right">Second source vector.</param>
		/// <returns>The cross product of the two vectors.</returns>
		static Vector3 Cross(Vector3 left, Vector3 right);

		/// <summary>
		/// Calculates the cross product of two vectors.
		/// </summary>
		/// <param name="left">First source vector.</param>
		/// <param name="right">Second source vector.</param>
		/// <param name="result">The cross product of the two vectors.</param>
		static void Cross(Vector3% left, Vector3% right, [Out] Vector3% result);

		btScalar Distance(Vector3 v);

		/// <summary>
		/// Calculates the distance between two vectors.
		/// </summary>
		/// <param name="value1">The first vector.</param>
		/// <param name="value2">The second vector.</param>
		/// <returns>The distance between the two vectors.</returns>
		static btScalar Distance(Vector3 value1, Vector3 value2);

		btScalar DistanceSquared(Vector3 v);

		/// <summary>
		/// Calculates the squared distance between two vectors.
		/// </summary>
		/// <param name="value1">The first vector.</param>
		/// <param name="value2">The second vector.</param>
		/// <returns>The squared distance between the two vectors.</returns>
		/// <remarks>Distance squared is the value before taking the square root. 
		/// Distance squared can often be used in place of distance if relative comparisons are being made. 
		/// For example, consider three points A, B, and C. To determine whether B or C is further from A, 
		/// compare the distance between A and B to the distance between A and C. Calculating the two distances 
		/// involves two square roots, which are computationally expensive. However, using distance squared 
		/// provides the same information and avoids calculating two square roots.
		/// </remarks>
		static btScalar DistanceSquared(Vector3 value1, Vector3 value2);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="value">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <returns>The scaled vector.</returns>
		static Vector3 Divide(Vector3 value, btScalar scale);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="vector">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <param name="result">When the method completes, contains the scaled vector.</param>
		static void Divide(Vector3% vector, btScalar scale, [Out] Vector3% result);

		/// <summary>
		/// Performs a Hermite spline interpolation.
		/// </summary>
		/// <param name="value1">First source position vector.</param>
		/// <param name="tangent1">First source tangent vector.</param>
		/// <param name="value2">Second source position vector.</param>
		/// <param name="tangent2">Second source tangent vector.</param>
		/// <param name="amount">Weighting factor.</param>
		/// <returns>The result of the Hermite spline interpolation.</returns>
		static Vector3 Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, btScalar amount);

		/// <summary>
		/// Performs a Hermite spline interpolation.
		/// </summary>
		/// <param name="value1">First source position vector.</param>
		/// <param name="tangent1">First source tangent vector.</param>
		/// <param name="value2">Second source position vector.</param>
		/// <param name="tangent2">Second source tangent vector.</param>
		/// <param name="amount">Weighting factor.</param>
		/// <param name="result">When the method completes, contains the result of the Hermite spline interpolation.</param>
		static void Hermite(Vector3% value1, Vector3% tangent1, Vector3% value2, Vector3% tangent2, btScalar amount, [Out] Vector3% result);

		btScalar Dot(Vector3 v);

		/// <summary>
		/// Calculates the dot product of two vectors.
		/// </summary>
		/// <param name="left">First source vector.</param>
		/// <param name="right">Second source vector.</param>
		/// <returns>The dot product of the two vectors.</returns>
		static btScalar Dot(Vector3 left, Vector3 right);

		Vector3 Dot3(Vector3 v0, Vector3 v1, Vector3 v2);
		void GetSkewSymmetricMatrix([Out] Vector3% v0, [Out] Vector3% v1, [Out] Vector3% v2);
		Vector3 Lerp(Vector3 v, btScalar amount);

		/// <summary>
		/// Performs a linear interpolation between two vectors.
		/// </summary>
		/// <param name="start">Start vector.</param>
		/// <param name="end">End vector.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <returns>The linear interpolation of the two vectors.</returns>
		/// <remarks>
		/// This method performs the linear interpolation based on the following formula.
		/// <code>start + (end - start) * amount</code>
		/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
		/// </remarks>
		static Vector3 Lerp(Vector3 start, Vector3 end, btScalar amount);

		/// <summary>
		/// Performs a linear interpolation between two vectors.
		/// </summary>
		/// <param name="start">Start vector.</param>
		/// <param name="end">End vector.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <param name="result">When the method completes, contains the linear interpolation of the two vectors.</param>
		/// <remarks>
		/// This method performs the linear interpolation based on the following formula.
		/// <code>start + (end - start) * amount</code>
		/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
		/// </remarks>
		static void Lerp(Vector3% start, Vector3% end, btScalar amount, [Out] Vector3% result);

		/// <summary>
		/// Returns a vector containing the largest components of the specified vectors.
		/// </summary>
		/// <param name="value1">The first source vector.</param>
		/// <param name="value2">The second source vector.</param>
		/// <returns>A vector containing the largest components of the source vectors.</returns>
		static Vector3 Maximize(Vector3 value1, Vector3 value2);

		/// <summary>
		/// Returns a vector containing the smallest components of the specified vectors.
		/// </summary>
		/// <param name="value1">The first source vector.</param>
		/// <param name="value2">The second source vector.</param>
		/// <param name="result">When the method completes, contains an new vector composed of the largest components of the source vectors.</param>
		static void Maximize(Vector3% value1, Vector3% value2, [Out] Vector3% result);

		/// <summary>
		/// Returns a vector containing the smallest components of the specified vectors.
		/// </summary>
		/// <param name="value1">The first source vector.</param>
		/// <param name="value2">The second source vector.</param>
		/// <returns>A vector containing the smallest components of the source vectors.</returns>
		static Vector3 Minimize(Vector3 value1, Vector3 value2);

		/// <summary>
		/// Returns a vector containing the smallest components of the specified vectors.
		/// </summary>
		/// <param name="value1">The first source vector.</param>
		/// <param name="value2">The second source vector.</param>
		/// <param name="result">When the method completes, contains an new vector composed of the smallest components of the source vectors.</param>
		static void Minimize(Vector3% value1, Vector3% value2, [Out] Vector3% result);
		/// <summary>
		/// Modulates a vector by another.
		/// </summary>
		/// <param name="left">The first vector to modulate.</param>
		/// <param name="right">The second vector to modulate.</param>
		/// <returns>The modulated vector.</returns>
		static Vector3 Modulate(Vector3 left, Vector3 right);

		/// <summary>
		/// Modulates a vector by another.
		/// </summary>
		/// <param name="left">The first vector to modulate.</param>
		/// <param name="right">The second vector to modulate.</param>
		/// <param name="result">When the moethod completes, contains the modulated vector.</param>
		static void Modulate(Vector3% left, Vector3% right, [Out] Vector3% result);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="value">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <returns>The scaled vector.</returns>
		static Vector3 Multiply(Vector3 value, btScalar scale);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="vector">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <param name="result">When the method completes, contains the scaled vector.</param>
		static void Multiply(Vector3% vector, btScalar scale, [Out] Vector3% result);


		/// <summary>
		/// Reverses the direction of a given vector.
		/// </summary>
		/// <param name="value">The vector to negate.</param>
		/// <returns>A vector facing in the opposite direction.</returns>
		static Vector3 Negate(Vector3 value);

		/// <summary>
		/// Reverses the direction of a given vector.
		/// </summary>
		/// <param name="value">The vector to negate.</param>
		/// <param name="result">When the method completes, contains a vector facing in the opposite direction.</param>
		static void Negate(Vector3% value, [Out] Vector3% result);

		/// <summary>
		/// Converts the vector into a unit vector.
		/// </summary>
		void Normalize();

		/// <summary>
		/// Converts the vector into a unit vector.
		/// </summary>
		/// <param name="vector">The vector to normalize.</param>
		/// <returns>The normalized vector.</returns>
		static Vector3 Normalize(Vector3 vector);

		/// <summary>
		/// Converts the vector into a unit vector.
		/// </summary>
		/// <param name="vector">The vector to normalize.</param>
		/// <param name="result">When the method completes, contains the normalized vector.</param>
		static void Normalize(Vector3% vector, [Out] Vector3% result);

		/// <summary>
		/// Projects a 3D vector from object space into screen space. 
		/// </summary>
		/// <param name="vector">The vector to project.</param>
		/// <param name="x">The X position of the viewport.</param>
		/// <param name="y">The Y position of the viewport.</param>
		/// <param name="width">The width of the viewport.</param>
		/// <param name="height">The height of the viewport.</param>
		/// <param name="minZ">The minimum depth of the viewport.</param>
		/// <param name="maxZ">The maximum depth of the viewport.</param>
		/// <param name="worldViewProjection">The combined world-view-projection matrix.</param>
		/// <returns>The vector in screen space.</returns>
		static Vector3 Project(Vector3 vector, btScalar x, btScalar y, btScalar width, btScalar height, btScalar minZ, btScalar maxZ, Matrix worldViewProjection);

		/// <summary>
		/// Projects a 3D vector from object space into screen space. 
		/// </summary>
		/// <param name="vector">The vector to project.</param>
		/// <param name="x">The X position of the viewport.</param>
		/// <param name="y">The Y position of the viewport.</param>
		/// <param name="width">The width of the viewport.</param>
		/// <param name="height">The height of the viewport.</param>
		/// <param name="minZ">The minimum depth of the viewport.</param>
		/// <param name="maxZ">The maximum depth of the viewport.</param>
		/// <param name="worldViewProjection">The combined world-view-projection matrix.</param>
		/// <param name="result">When the method completes, contains the vector in screen space.</param>
		static void Project(Vector3% vector, btScalar x, btScalar y, btScalar width, btScalar height, btScalar minZ, btScalar maxZ, Matrix% worldViewProjection, [Out] Vector3% result);

		/// <summary>
		/// Returns the reflection of a vector off a surface that has the specified normal. 
		/// </summary>
		/// <param name="vector">The source vector.</param>
		/// <param name="normal">Normal of the surface.</param>
		/// <returns>The reflected vector.</returns>
		/// <remarks>Reflect only gives the direction of a reflection off a surface, it does not determine 
		/// whether the original vector was close enough to the surface to hit it.</remarks>
		static Vector3 Reflect(Vector3 vector, Vector3 normal);

		/// <summary>
		/// Returns the reflection of a vector off a surface that has the specified normal. 
		/// </summary>
		/// <param name="vector">The source vector.</param>
		/// <param name="normal">Normal of the surface.</param>
		/// <param name="result">When the method completes, contains the reflected vector.</param>
		/// <remarks>Reflect only gives the direction of a reflection off a surface, it does not determine 
		/// whether the original vector was close enough to the surface to hit it.</remarks>
		static void Reflect(Vector3% vector, Vector3% normal, [Out] Vector3% result);

		Vector3 Rotate(Vector3 wAxis, btScalar angle);
		void SetInterpolate3(Vector3 v0, Vector3 v1, btScalar rt);
		void SetMax(Vector3 other);
		void SetMin(Vector3 other);

		/// <summary>
		/// Sets all components to 0.
		/// </summary>
		void SetZero();

		/// <summary>
		/// Performs a cubic interpolation between two vectors.
		/// </summary>
		/// <param name="start">Start vector.</param>
		/// <param name="end">End vector.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <returns>The cubic interpolation of the two vectors.</returns>
		static Vector3 SmoothStep(Vector3 start, Vector3 end, btScalar amount);

		/// <summary>
		/// Performs a cubic interpolation between two vectors.
		/// </summary>
		/// <param name="start">Start vector.</param>
		/// <param name="end">End vector.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <param name="result">When the method completes, contains the cubic interpolation of the two vectors.</param>
		static void SmoothStep(Vector3% start, Vector3% end, btScalar amount, [Out] Vector3% result);

		/// <summary>
		/// Subtracts two vectors.
		/// </summary>
		/// <param name="left">The first vector to subtract.</param>
		/// <param name="right">The second vector to subtract.</param>
		/// <returns>The difference of the two vectors.</returns>
		static Vector3 Subtract(Vector3 left, Vector3 right);

		/// <summary>
		/// Subtracts two vectors.
		/// </summary>
		/// <param name="left">The first vector to subtract.</param>
		/// <param name="right">The second vector to subtract.</param>
		/// <param name="result">When the method completes, contains the difference of the two vectors.</param>
		static void Subtract(Vector3% left, Vector3% right, [Out] Vector3% result);

		void SetValue(btScalar x, btScalar y, btScalar z);

		/// <summary>
		/// Transforms a 3D vector by the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="vector">The source vector.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
		static Vector4 Transform(Vector3 vector, Matrix transformation);

		/// <summary>
		/// Transforms a 3D vector by the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="vector">The source vector.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
		static void Transform(Vector3% vector, Matrix% transformation, [Out] Vector4% result);

		/// <summary>
		/// Transforms an array of 3D vectors by the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="vectors">The source vectors.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <returns>The transformed <see cref="SlimDX::Vector4"/>s.</returns>
		static array<Vector4>^ Transform(array<Vector3>^ vectors, Matrix% transformation);

		/// <summary>
		/// Transforms a 3D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
		/// </summary>
		/// <param name="vector">The vector to rotate.</param>
		/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
		/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
		static Vector4 Transform(Vector3 vector, Quaternion rotation);

		/// <summary>
		/// Transforms a 3D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
		/// </summary>
		/// <param name="vector">The vector to rotate.</param>
		/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
		/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
		static void Transform(Vector3% vector, Quaternion% rotation, [Out] Vector4% result);

		/// <summary>
		/// Transforms an array of 3D vectors by the given <see cref="SlimDX::Quaternion"/> rotation.
		/// </summary>
		/// <param name="vectors">The vectors to rotate.</param>
		/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
		/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
		static array<Vector4>^ Transform(array<Vector3>^ vectors, Quaternion% rotation);

		/// <summary>
		/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="coordinate">The coordinate vector to transform.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <returns>The transformed coordinates.</returns>
		static Vector3 TransformCoordinate(Vector3 coordinate, Matrix transformation);

		/// <summary>
		/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="coordinate">The coordinate vector to transform.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <param name="result">When the method completes, contains the transformed coordinates.</param>
		static void TransformCoordinate(Vector3% coordinate, Matrix% transformation, [Out] Vector3% result);

		/// <summary>
		/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="normal">The normal vector to transform.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <returns>The transformed normal.</returns>
		static Vector3 TransformNormal(Vector3 normal, Matrix transformation);

		/// <summary>
		/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
		/// </summary>
		/// <param name="normal">The normal vector to transform.</param>
		/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
		/// <param name="result">When the method completes, contains the transformed normal.</param>
		static void TransformNormal(Vector3% normal, Matrix% transformation, [Out] Vector3% result);

		btScalar Triple(Vector3 v1, Vector3 v2);

		property Vector3 Absolute
		{
			Vector3 get();
		}

		property int ClosestAxis
		{
			int get();
		}

		property int FurthestAxis
		{
			int get();
		}

		property bool IsFuzzyZero
		{
			bool get();
		}

		property bool IsZero
		{
			bool get();
		}

		/// <summary>
		/// Calculates the length of the vector.
		/// </summary>
		/// <value>The length of the vector.</value>
		property btScalar Length
		{
			btScalar get();
		}

		/// <summary>
		/// Calculates the squared length of the vector.
		/// </summary>
		/// <value>The squared length of the vector.</value>
		property btScalar LengthSquared
		{
			btScalar get();
		}

		property int MaxAxis
		{
			int get();
		}

		property int MinAxis
		{
			int get();
		}

		property Vector3 Normalized
		{
			Vector3 get();
		}

		/// <summary>
		/// Adds two vectors.
		/// </summary>
		/// <param name="left">The first vector to add.</param>
		/// <param name="right">The second vector to add.</param>
		/// <returns>The sum of the two vectors.</returns>
		static Vector3 operator + (Vector3 left, Vector3 right);

		/// <summary>
		/// Subtracts two vectors.
		/// </summary>
		/// <param name="left">The first vector to subtract.</param>
		/// <param name="right">The second vector to subtract.</param>
		/// <returns>The difference of the two vectors.</returns>
		static Vector3 operator - (Vector3 left, Vector3 right);

		/// <summary>
		/// Reverses the direction of a given vector.
		/// </summary>
		/// <param name="value">The vector to negate.</param>
		/// <returns>A vector facing in the opposite direction.</returns>
		static Vector3 operator - (Vector3 value);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="vector">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <returns>The scaled vector.</returns>
		static Vector3 operator * (Vector3 vector, btScalar scale);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="vector">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <returns>The scaled vector.</returns>
		static Vector3 operator * (btScalar scale, Vector3 vector);

		/// <summary>
		/// Modulates a vector by another.
		/// </summary>
		/// <param name="left">The first vector to modulate.</param>
		/// <param name="right">The second vector to modulate.</param>
		/// <returns>The modulated vector.</returns>
		static Vector3 operator * (Vector3 left, Vector3 right);

		/// <summary>
		/// Scales a vector by the given value.
		/// </summary>
		/// <param name="vector">The vector to scale.</param>
		/// <param name="scale">The amount by which to scale the vector.</param>
		/// <returns>The scaled vector.</returns>
		static Vector3 operator / (Vector3 vector, btScalar scale);

		/// <summary>
		/// Tests for equality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator == (Vector3 left, Vector3 right);

		/// <summary>
		/// Tests for inequality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator != (Vector3 left, Vector3 right);

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
		virtual bool Equals(Vector3 other);

		/// <summary>
		/// Determines whether the specified object instances are considered equal. 
		/// </summary>
		/// <param name="value1">The first value to compare.</param>
		/// <param name="value2">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
		/// if both are <c>null</c> references or if <c>value1.Equals(value2)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
		static bool Equals(Vector3% value1, Vector3% value2);
	};
}
