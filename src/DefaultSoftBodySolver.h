#pragma once

#include "SoftBodySolver.h"

namespace BulletSharp
{
	namespace SoftBody
	{
		ref class SoftBody;
		ref class VertexBufferDescriptor;

		public ref class DefaultSoftBodySolver : SoftBodySolver
		{
		internal:
			DefaultSoftBodySolver(btDefaultSoftBodySolver* native);

		public:
			DefaultSoftBodySolver();

			void CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer);
		};
	};
};
