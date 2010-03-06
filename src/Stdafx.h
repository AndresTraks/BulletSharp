// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#if GRAPHICS_XNA31
	#using <Microsoft.Xna.Framework.dll>
#elif GRAPHICS_SLIMDX
#if WIN32
	#using <x86/SlimDX.dll>
#elif WIN64
	#using <x64/SlimDX.dll>
#endif
#else
	#error No Graphics Target Specified
#endif

#if GRAPHICS_XNA31
	#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
	#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_SLIMDX
	#define UsingFrameworkNamespace using namespace SlimDX;
	#define UsingGraphicsNamespace using namespace SlimDX::Direct3D9;
#endif

#pragma managed(push, off)

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#pragma managed(pop)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Math.h"

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

using namespace BulletSharp;
