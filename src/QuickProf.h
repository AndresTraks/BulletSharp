#pragma once

namespace BulletSharp
{
#ifdef USE_BT_CLOCK
	public ref class Clock
	{
	internal:
		btClock* _native;

		Clock(btClock* native);

		~Clock();
		!Clock();

	public:
		Clock();
		Clock(Clock^ other);

		Clock^ operator=(Clock^ other);
		void Reset();

		property unsigned long TimeMicroseconds
		{
			unsigned long get();
		}

		property unsigned long TimeMilliseconds
		{
			unsigned long get();
		}

		property btScalar TimeSeconds
		{
			btScalar get();
		}
	};
#endif

	public ref class CProfileNode
	{
	internal:
		::CProfileNode* _native;
		CProfileNode(::CProfileNode* native);

	public:
		//CProfileNode(String^ name, CProfileNode^ parent);

		void Call();
		void CleanupMemory();
		//CProfileNode^ GetSubNode(String^ name);
		void Reset();
		bool Return();

		property CProfileNode^ Child
		{
			CProfileNode^ get();
		}

		property String^ Name
		{
			String^ get();
		}

		property CProfileNode^ Parent
		{
			CProfileNode^ get();
		}

		property CProfileNode^ Sibling
		{
			CProfileNode^ get();
		}

		property int TotalCalls
		{
			int get();
		}

		property float TotalTime
		{
			float get();
		}

		property IntPtr UserPointer
		{
			IntPtr get();
			void set(IntPtr ptr);
		}
	};

	public ref class CProfileIterator
	{
	internal:
		::CProfileIterator* _native;
		CProfileIterator(::CProfileIterator* native);

	public:
		//CProfileIterator();

		void EnterChild(int index);
		//void EnterLargestChild();
		void EnterParent();
		void First();
		void Next();

		property String^ CurrentName
		{
			String^ get();
		}

		property String^ CurrentParentName
		{
			String^ get();
		}

		property int CurrentParentTotalCalls
		{
			int get();
		}

		property float CurrentParentTotalTime
		{
			float get();
		}

		property int CurrentTotalCalls
		{
			int get();
		}

		property float CurrentTotalTime
		{
			float get();
		}

		property IntPtr CurrentUserPointer
		{
			IntPtr get();
			void set(IntPtr ptr);
		}

		property bool IsDone
		{
			bool get();
		}

		property bool IsRoot
		{
			bool get();
		}
	};

	public ref class CProfileManager sealed
	{
		CProfileManager() {}

	public:
		static void CleanupMemory();
		static void DumpAll();
		static void DumpRecursive(CProfileIterator^ profileIterator, int spacing);
		static void IncrementFrameCounter();
		static void ReleaseIterator(CProfileIterator^ iterator);
		static void Reset();
		//static void StartProfile(String^ name);
		static void StopProfile();

		property int FrameCountSinceReset
		{
			static int get();
		}

		property CProfileIterator^ Iterator
		{
			static CProfileIterator^ get();
		}

		property float TimeSinceReset
		{
			static float get();
		}
	};

	public ref class CProfileSample
	{
	internal:
		::CProfileSample* _native;

		CProfileSample(::CProfileSample* native);

	public:
		//CProfileSample(String^ name);
	};
};
