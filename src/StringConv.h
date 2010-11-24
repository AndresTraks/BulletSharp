#pragma once

#define PinManagedString(string) return PtrToStringChars(string);

namespace BulletSharp
{
	private ref class StringConv
	{
	public:
		static String^ UnmanagedToManaged(const char* string);
		static const char* ManagedToUnmanaged(String^ string);
		static void FreeUnmanagedString(const char* string);
	};
};
