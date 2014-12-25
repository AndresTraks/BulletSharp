#pragma once

namespace BulletSharp
{
	ref class UIntArray;

	namespace MultiThreaded
	{
		public ref class Barrier //abstract
		{
		internal:
			btBarrier* _native;
			Barrier(btBarrier* native);

		public:
			void Sync();

			property int MaxCount
			{
				int get();
				void set(int n);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		public ref class CriticalSection //abstract
		{
		internal:
			btCriticalSection* _native;
			CriticalSection(btCriticalSection* native);

		public:
			unsigned int GetSharedParam(int i);
			void Lock();
			void SetSharedParam(int i, unsigned int p);
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

		public ref class ThreadSupportInterface abstract
		{
		internal:
			btThreadSupportInterface* _native;
			ThreadSupportInterface(btThreadSupportInterface* native);

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
				void set(int numTasks);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};
	};
};
