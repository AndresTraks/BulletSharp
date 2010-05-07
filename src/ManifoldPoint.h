#pragma once

namespace BulletSharp
{
	public ref class ManifoldPoint
	{
	private:
		btManifoldPoint* _point;
	
	public:
		ManifoldPoint();

	internal:
		property btManifoldPoint* UnmanagedPointer
		{
			virtual btManifoldPoint* get();
			void set(btManifoldPoint* value);
		}
	};
};
