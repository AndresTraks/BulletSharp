#pragma once

namespace BulletSharp
{
	public ref class MLCPSolverInterface abstract
	{
	internal:
		btMLCPSolverInterface* _native;
		MLCPSolverInterface(btMLCPSolverInterface* native);

	public:
		//bool SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi,
		//	AlignedObjectArray^ limitDependency, int numIterations, bool useSparsity);
		//bool SolveMLCP(MatrixXf^ A, VectorXf^ b, VectorXf^ x, VectorXf^ lo, VectorXf^ hi,
		//	AlignedObjectArray^ limitDependency, int numIterations);
	};
};
