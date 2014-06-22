#pragma once

namespace BulletSharp
{
	public interface class ITrackingDisposable : System::IDisposable
	{
	public:
		event EventHandler^ OnDisposing;
		event EventHandler^ OnDisposed;

		property bool IsDisposed
		{
			bool get();
		}
	};
};