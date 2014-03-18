#pragma once

using namespace System::Collections::Generic;

namespace BulletSharp
{
	public ref class Hacd
	{
	internal:
		HACD::HACD* _native;

	private:
		HACD::Vec3<HACD::Real>* _points;
		HACD::Vec3<long>* _triangles;

	public:
		Hacd();

		bool Compute(bool fullCH, bool exportDistPoints);
		bool Compute(bool fullCH);
		bool Compute();
		void DenormalizeData();
		bool GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles);
		int GetNPointsCH(int numCH);
		int GetNTrianglesCH(int numCH);
		void NormalizeData();
		bool Save(String^ fileName, bool uniColor, long numCluster);
		bool Save(String^ fileName, bool uniColor);
		void SetPoints(ICollection<Vector3>^ points);
		void SetTriangles(ICollection<long>^ points);

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
/*
		property CallBackFunction CallBack
		{
			CallBackFunction get();
			void set(CallBackFunction callBack);
		}
*/
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

		property int NVerticesPerCH
		{
			int get();
			void set(int nVerticesPerCH);
		}
/*
		property LongArray Partition
		{
			LongArray get();
		}

		property Vec3^ Points
		{
			Vec3^ get();
			void set(Vec3^ points);
		}
*/
		property double ScaleFactor
		{
			double get();
			void set(double scale);
		}
/*
		property Vec3^ Triangles
		{
			Vec3^ get();
			void set(Vec3^ triangles);
		}
*/
		property double VolumeWeight
		{
			double get();
			void set(double beta);
		}
	};
};
