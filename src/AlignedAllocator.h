#pragma once

namespace BulletSharp
{
	public ref class AlignedAllocator abstract sealed
	{
	public:
		static property int NumAlignedAllocs
		{
			int get();
		}

		static property int NumAlignedFrees
		{
			int get();
		}
	};
};
