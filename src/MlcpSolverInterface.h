#pragma once

namespace BulletSharp
{
	public ref class MlcpSolverInterface abstract
	{
	internal:
		btMLCPSolverInterface* _native;

		MlcpSolverInterface(btMLCPSolverInterface* native);

		~MlcpSolverInterface();
		!MlcpSolverInterface();

	public:
		//bool SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi,
		//	AlignedObjectArray^ limitDependency, int numIterations, bool useSparsity);
		//bool SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi,
		//	AlignedObjectArray^ limitDependency, int numIterations);
	};
};
