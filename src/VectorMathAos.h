#pragma once

#pragma managed(push, off)
#include "vectormath/vmInclude.h"
#pragma managed(pop)

namespace BulletSharp
{
	namespace VectorMath
	{
		namespace Aos
		{
			ref class VMVector3;

			public ref class Matrix3
			{
			private:
				Vectormath::Aos::Matrix3* _matrix;

			public:
				Matrix3(VMVector3^ col0, VMVector3^ col1, VMVector3^ col2);

				static VMVector3^ operator*(Matrix3^ matrix, VMVector3^ vec);

			internal:
				property Vectormath::Aos::Matrix3* UnmanagedPointer
				{
					Vectormath::Aos::Matrix3* get();
				}
			};

			public ref class VMVector3
			{
			private:
				Vectormath::Aos::Vector3* _vector;

			internal:
				VMVector3(Vectormath::Aos::Vector3* vector);

			public:
				VMVector3();
				VMVector3(float x, float y, float z);

				property float X
				{
					float get();
				}

				property float Y
				{
					float get();
				}

				property float Z
				{
					float get();
				}

			internal:
				property Vectormath::Aos::Vector3* UnmanagedPointer
				{
					Vectormath::Aos::Vector3* get();
				}
			};
		};
	};
};
