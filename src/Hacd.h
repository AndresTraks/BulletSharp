#pragma once

using namespace System::Collections::Generic;

namespace BulletSharp
{
	namespace Hacd
	{
		public ref class Hacd
		{
		internal:
			HACD::HACD* _unmanaged;

		private:
			HACD::Vec3<HACD::Real>* _points;
			HACD::Vec3<long>* _triangles;

		public:
			Hacd();

			bool Compute();
			bool GetCH(int numCH, [Out] array<Vector3>^% points, [Out] array<long>^% triangles);
			int GetNPointsCH(int numCH);
			int GetNTrianglesCH(int numCH);
			bool Save(String^ fileName, bool uniColor, long numCluster);
			bool Save(String^ fileName, bool uniColor);
			void SetPoints(ICollection<Vector3>^ points);
			void SetTriangles(ICollection<long>^ points);

			property bool AddExtraDistPoints
			{
				bool get();
				void set(bool value);
			}

			property bool AddFacesPoints
			{
				bool get();
				void set(bool value);
			}

			property bool AddNeighboursDistPoints
			{
				bool get();
				void set(bool value);
			}

			property double CompacityWeight
			{
				double get();
				void set(double value);
			}

			property double Concavity
			{
				double get();
				void set(double value);
			}

			property int NClusters
			{
				int get();
				void set(int value);
			}

			property int NPoints
			{
				int get();
			}

			property int VerticesPerConvexHull
			{
				int get();
				void set(int value);
			}

			property double VolumeWeight
			{
				double get();
				void set(double value);
			}
		};
	};
};
