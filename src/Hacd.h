#pragma once

namespace BulletSharp
{
	public ref class Hacd
	{
	internal:
		HACD::HACD* _native;

	private:
		[UnmanagedFunctionPointer(CallingConvention::Cdecl), SuppressUnmanagedCodeSecurity]
		delegate bool CallbackFunctionUnmanagedDelegate(IntPtr msg,
			double progress, double globalConcavity, IntPtr n);
	public:
		delegate bool CallBackFunction(String^ msg, double progress, double globalConcativity, int n);

	private:
		HACD::Vec3<HACD::Real>* _points;
		HACD::Vec3<long>* _triangles;
		CallbackFunctionUnmanagedDelegate^ _callbackFunctionUnmanaged;
		CallBackFunction^ _callbackFunction;

		~Hacd();
		!Hacd();

	private:
		bool CallbackFunctionUnmanaged(IntPtr msg, double progress, double globalConcavity, IntPtr n);

	public:
		Hacd();

		bool Compute(bool fullCH, bool exportDistPoints);
		bool Compute(bool fullCH);
		bool Compute();
		void DenormalizeData();
		bool GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles);
		int GetNPointsCH(int numCH);
		int GetNTrianglesCH(int numCH);
		array<HACD::Real>^ GetPoints();
		array<Int64>^ GetTriangles();
		void NormalizeData();
		bool Save(String^ fileName, bool uniColor, long numCluster);
		bool Save(String^ fileName, bool uniColor);
		void SetPoints(ICollection<HACD::Real>^ points);
		void SetPoints(ICollection<Vector3>^ points);
		void SetTriangles(ICollection<long>^ points);
		void SetTriangles(ICollection<int>^ points);

		property bool AddExtraDistPoints
		{
			bool get();
			void set(bool addExtraDistPoints);
		}

		property bool AddFacesPoints
		{
			bool get();
			void set(bool addFacesPoints);
		}

		property bool AddNeighboursDistPoints
		{
			bool get();
			void set(bool addNeighboursDistPoints);
		}

		property CallBackFunction^ CallBack
		{
			CallBackFunction^ get();
			void set(CallBackFunction^ callBack);
		}

		property double CompacityWeight
		{
			double get();
			void set(double alpha);
		}

		property double Concavity
		{
			double get();
			void set(double concavity);
		}

		property double ConnectDist
		{
			double get();
			void set(double ccConnectDist);
		}

		property int NClusters
		{
			int get();
			void set(int nClusters);
		}

		property int NPoints
		{
			int get();
			void set(int nPoints);
		}

		property int NTriangles
		{
			int get();
			void set(int nTriangles);
		}

		property int NumVerticesPerConvexHull
		{
			int get();
			void set(int nVerticesPerCH);
		}
/*
		property LongArray Partition
		{
			LongArray get();
		}
*/
		property double ScaleFactor
		{
			double get();
			void set(double scale);
		}

		property double VolumeWeight
		{
			double get();
			void set(double beta);
		}
	};
};
