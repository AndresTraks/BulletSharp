#pragma once

namespace BulletSharp
{
	namespace SoftBody
	{
		ref class AlignedSoftBodyArray;
		ref class SoftBody;
		ref class VertexBufferDescriptor;

		public ref class SoftBodySolver
		{
		private:
			btSoftBodySolver* _solver;

		internal:
			SoftBodySolver(btSoftBodySolver* solver);

		public:
			void Optimize(AlignedSoftBodyArray^ softBodies);
			void CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer);

			property int NumberOfPositionIterations
			{
				int get();
				void set(int value);
			}

			property int NumberOfVelocityIterations
			{
				int get();
				void set(int value);
			}

			property float TimeScale
			{
				float get();
			}

		internal:
			property btSoftBodySolver* UnmanagedPointer
			{
				btSoftBodySolver* get();
				void set(btSoftBodySolver* value);
			}
		};
	};
};
