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
		};

		public ref class SoftBodySolverOutput
		{
		internal:
			btSoftBodySolverOutput* _native;

			SoftBodySolverOutput(btSoftBodySolverOutput* solverOutput);

		public:
			void CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer);
		};
	};
};
