#pragma once

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionObjectWrapper;

	namespace SoftBody
	{
		ref class AlignedSoftBodyArray;
		ref class SoftBody;
		ref class VertexBufferDescriptor;

		public ref class SoftBodySolver abstract
		{
		internal:
			btSoftBodySolver* _native;
			SoftBodySolver(btSoftBodySolver* native);

		public:
			!SoftBodySolver();
		protected:
			~SoftBodySolver();

		public:
			bool CheckInitialized();
			void CopyBackToSoftBodies(bool bMove);
			void CopyBackToSoftBodies();
			void Optimize(AlignedSoftBodyArray^ softBodies, bool forceUpdate);
			void Optimize(AlignedSoftBodyArray^ softBodies);
			void PredictMotion(float solverdt);
			void ProcessCollision(SoftBody^ softBody, CollisionObjectWrapper^ collisionObjectWrapper);
			void ProcessCollision(SoftBody^ softBody, SoftBody^ otherSoftBody);
			void SolveConstraints(float solverdt);
			void UpdateSoftBodies();

			property int NumberOfPositionIterations
			{
				int get();
				void set(int iterations);
			}

			property int NumberOfVelocityIterations
			{
				int get();
				void set(int iterations);
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

		public ref class SoftBodySolverOutput abstract
		{
		internal:
			btSoftBodySolverOutput* _native;
			SoftBodySolverOutput(btSoftBodySolverOutput* native);

		public:
			void CopySoftBodyToVertexBuffer(SoftBody^ softBody, VertexBufferDescriptor^ vertexBuffer);
		};
	};
};
