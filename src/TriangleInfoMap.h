#pragma once

namespace BulletSharp
{
	public ref class TriangleInfoMap
	{
	private:
		btTriangleInfoMap* _triangleInfoMap;

	public:
		TriangleInfoMap();

	internal:
		property btTriangleInfoMap* UnmanagedPointer
		{
			virtual btTriangleInfoMap* get();
			void set(btTriangleInfoMap* value);
		}
	};
};
