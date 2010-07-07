#pragma once

// Fully implemented as of 07 Jul 2010

#include "IDisposable.h"

#pragma managed(push, off)
#include <BulletMultiThreaded/btThreadSupportInterface.h>
#pragma managed(pop)

namespace BulletSharp
{
	namespace MultiThreaded
	{
		public ref class Barrier : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btBarrier* _barrier;

		internal:
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

		public ref class CriticalSection : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btCriticalSection* _criticalSection;

		internal:
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

			property array<unsigned int>^ CommonBuff
			{
				array<unsigned int>^ get();
				void set(array<unsigned int>^ value);
			}

			property bool IsDisposed
			{
				virtual bool get();
			}
		};

		public ref class ThreadSupportInterface : BulletSharp::IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			btThreadSupportInterface* _threadSupport;

		internal:
			ThreadSupportInterface(btThreadSupportInterface* threadSupport);

		public:
			!ThreadSupportInterface();
		protected:
			~ThreadSupportInterface();

		public:
			Barrier^ CreateBarrier();
			CriticalSection^ CreateCriticalSection();
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

			property btThreadSupportInterface* UnmanagedPointer
			{
				btThreadSupportInterface* get();
			}
		};
	};
};
