/*
* Copyright (c) 2007-2009 SlimDX Group
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

#ifdef XMLDOCS
using System::ArgumentException;
using System::ArgumentNullException;
using System::ArgumentOutOfRangeException;
#endif

namespace BulletSharp
{
	ref class DataStream;

	ref class Utilities sealed
	{
	private:
		Utilities();
		
	public:
		//These doc comments are mostly intended to copy to other places.

		/// <summary>
		/// Checks that a range to be read are within the boundaries of a source.
		/// </summary>
		/// <param name="lowerBound">The minimum bound that can be read from the source, and fills in the number of elements to read if necessary.</param>
		/// <param name="size">The total size of the source.</param>
		/// <param name="offset">The index at which the caller intends to begin reading from the source.</param>
		/// <param name="count">The number of elements intended to be read from the source. If 0 is passed, count will be adjusted to be size - offset.</param>
		/// <exception cref="ArgumentOutOfRangeException"><paramref name="offset" /> is less than <paramref name="lowerBound" />.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><paramref name="count" /> is negative.</exception>
		/// <exception cref="ArgumentException">The sum of <paramref name="offset" /> and <paramref name="count" /> is greater than the buffer length.</exception>
		static void CheckBounds( int lowerBound, int size, int offset, int% count );

		/// <summary>
		/// Checks that a range to be read is within the boundaries of a source array, and fills in the number of elements to read if necessary.
		/// </summary>
		/// <param name="data">The source array to be read from.</param>
		/// <param name="offset">The index at which the caller intends to begin reading from the source.</param>
		/// <param name="count">The number of elements intended to be read from the source. If 0 is passed, count will be adjusted to be size - offset.</param>
		/// <exception cref="ArgumentNullException"><paramref name="data" /> is a null reference.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><paramref name="offset" /> or <paramref name="count" /> is negative.</exception>
		/// <exception cref="ArgumentException">The sum of <paramref name="offset" /> and <paramref name="count" /> is greater than the buffer length.</exception>
		static void CheckArrayBounds( System::Array^ data, int offset, int% count );
	};
}
