#include "StdAfx.h"

#include "StringConv.h"

String^ StringConv::UnmanagedToManaged(const char* string)
{
	return Marshal::PtrToStringAnsi((IntPtr)(char*)string);
}

const char* StringConv::ManagedToUnmanaged(String^ string)
{
	return (const char*)Marshal::StringToHGlobalAnsi(string).ToPointer();
}

void StringConv::FreeUnmanagedString(const char* string)
{
	Marshal::FreeHGlobal(IntPtr((void*)string));
}
