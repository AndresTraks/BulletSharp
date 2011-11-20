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

			void Compute();
			void SetPoints(ICollection<Vector3>^ points);
			void SetTriangles(ICollection<int>^ points);
			void SetTriangles(ICollection<long>^ points);

			property double CompacityWeight
			{
				double get();
				void set(double value);
			}
		};
	};
};
