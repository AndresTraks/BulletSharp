#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	public ref class QuantizedBvh : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btQuantizedBvh* _bvh;

	internal:
		QuantizedBvh(btQuantizedBvh* bvh);

	public:
		!QuantizedBvh();
	protected:
		~QuantizedBvh();

	public:
		QuantizedBvh();

		//static QuantizedBvh^ DeserializeInPlace(IntPtr i_alignedDataBuffer, unsigned int i_dataBufferSize, bool i_swapEndian);

		void BuildInternal();

#ifndef DISABLE_SERIALIZE
		unsigned int CalculateSerializeBufferSize();

		static property unsigned int AlignmentSerializationPadding
		{
			unsigned int get();
		}
#endif

		property bool IsDisposed
		{
			virtual bool get();
		}

	internal:
		property btQuantizedBvh* UnmanagedPointer
		{
			btQuantizedBvh* get();
			void set(btQuantizedBvh* value);
		}
	};
};
