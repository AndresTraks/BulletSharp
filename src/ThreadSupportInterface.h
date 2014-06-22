#pragma once

namespace BulletSharp
{
	ref class UIntArray;

	namespace MultiThreaded
	{
		public ref class Barrier : IDisposable
		{
		internal:
			btBarrier* _native;

			Barrier(btBarrier* barrier);

		public:
			!Barrier();
		protected:
			~Barrier();

		public:
			void Sync();

			property int MaxCount
			{
				int get();
				void set(int value);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		public ref class CriticalSection : IDisposable
		{
		internal:
			btCriticalSection* _native;

			CriticalSection(btCriticalSection* criticalSection);

		public:
			!CriticalSection();
		protected:
			~CriticalSection();

		public:
			unsigned int GetSharedParam(int i);
			void SetSharedParam(int i, unsigned int p);
			void Lock();
			void Unlock();

			property UIntArray^ CommonBuff
			{
				UIntArray^ get();
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		public ref class ThreadSupportInterface abstract : IDisposable
		{
		internal:
			btThreadSupportInterface* _native;

			ThreadSupportInterface(btThreadSupportInterface* threadSupport);

		public:
			!ThreadSupportInterface();
		protected:
			~ThreadSupportInterface();

		public:
			Barrier^ CreateBarrier();
			CriticalSection^ CreateCriticalSection();
			void DeleteBarrier(Barrier^ barrier);
			void DeleteCriticalSection(CriticalSection^ criticalSection);
			IntPtr GetThreadLocalMemory(int taskId);
			void SendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1);
			void StartSpu();
			void StopSpu();
			void WaitForResponse([Out] unsigned int% puiArgument0, [Out] unsigned int% puiArgument1);

			property int NumTasks
			{
				int get();
				void set(int value);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};
	};
};
