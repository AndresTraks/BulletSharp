#pragma once

namespace BulletSharp
{
	ref class CollisionObject;

	namespace SoftBody
	{
		ref class AlignedSoftBodyArray;
		ref class SoftBody;
		ref class VertexBufferDescriptor;

		public ref class SoftBodySolver
		{
		internal:
			btSoftBodySolver* _native;
			SoftBodySolver(btSoftBodySolver* solver);

		public:
			void CopyBackToSoftBodies(bool bMove);
			void CopyBackToSoftBodies();
			void Optimize(AlignedSoftBodyArray^ softBodies, bool forceUpdate);
			void Optimize(AlignedSoftBodyArray^ softBodies);
			void ProcessCollision(SoftBody^ softBody, CollisionObjectWrapper^ collisionObjectWrapper);
			void ProcessCollision(SoftBody^ softBody, SoftBody^ otherSoftBody);

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

			property SolverType SolverType
			{
				BulletSharp::SolverType get();
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

		public ref class SoftBodySolverOutput
		{
		private:
			btSoftBodySolverOutput* _solverOutput;

		internal:
			SoftBodySolverOutput(btSoftBodySolverOutput* solverOutput);

		public:
			void CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer);

		internal:
			property btSoftBodySolverOutput* UnmanagedPointer
			{
				btSoftBodySolverOutput* get();
				void set(btSoftBodySolverOutput* value);
			}
		};
	};
};
