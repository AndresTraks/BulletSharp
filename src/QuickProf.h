#pragma once

namespace BulletSharp
{
#ifdef USE_BT_CLOCK
	public ref class Clock
	{
	internal:
		btClock* _native;

	public:
		Clock();
		Clock(Clock^ other);

		void Reset();

		property long TimeMicroseconds
		{
			long get();
		}

		property long TimeMilliseconds
		{
			long get();
		}
	};
#endif
}
