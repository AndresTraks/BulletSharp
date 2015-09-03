#pragma once

namespace BulletSharp
{
	[Flags]
	public enum class CpuFeatures
	{
		None = 0,
		Fma3 = 1,
		Sse4 = 2,
		NeonHpfp = 4
	};

	public ref class CpuFeatureUtility sealed
	{
	private:
		CpuFeatureUtility() {}
	public:
		property BulletSharp::CpuFeatures CpuFeatures
		{
			static BulletSharp::CpuFeatures get();
		}
	};
};
