#pragma once

namespace BulletSharp
{
#ifdef USE_BT_CLOCK
	public ref class Clock
	{
	private:
		btClock* _clock;

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

	internal:
		property btClock* UnmanagedPointer
		{
			btClock* get();
		}
	};
#endif
}
