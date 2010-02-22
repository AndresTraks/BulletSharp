#pragma once

namespace BulletSharp
{
	public interface class IDispatcher
	{
		public:
			property btDispatcher* UnmanagedPointer
			{
				virtual btDispatcher* get();
			}
	};
};
