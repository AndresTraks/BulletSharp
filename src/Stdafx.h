// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

// Use int instead of the framework-specific classes to marshal color values.
//#define USE_INT_COLOR


// These flags can be used to disable parts of the library that are not needed.

#define DISABLE_BVH
//#define DISABLE_COLLISION_ALGORITHMS
//#define DISABLE_CONSTRAINTS
#define DISABLE_DBVT
//#define DISABLE_DEBUGDRAW
//#define DISABLE_GIMPACT
//#define DISABLE_INTERNAL
//#define DISABLE_MULTITHREADED
//#define DISABLE_SERIALIZE
//#define DISABLE_SOFTBODY
#define DISABLE_VECTORMATH_AOS
//#define DISABLE_VEHICLE


// When using CMake to compile Bullet and double precision is specified,
// then this setting isn't applied to BulletSharp automatically.
// In this case, uncomment this line:
//#define BT_USE_DOUBLE_PRECISION


#define USE_MINICL
//#define USE_AMD_OPENCL


#if GRAPHICS_XNA31
	#using <Microsoft.Xna.Framework.dll>
#elif GRAPHICS_XNA40
	#using <Microsoft.Xna.Framework.dll>
#elif GRAPHICS_SLIMDX
#if WIN32
	#using <x86/SlimDX.dll>
#elif WIN64
	#using <x64/SlimDX.dll>
#endif
#elif GRAPHICS_SLIMMATH
	#using <SlimMath.dll>
#elif GRAPHICS_MOGRE
	#if _DEBUG
	#using <Mogre_d.dll>
	#else
	#using <Mogre.dll>
#endif
#elif GRAPHICS_OPENTK
	#using <OpenTK.dll>
#elif GRAPHICS_AXIOM
	#using <Axiom.dll>
#elif GRAPHICS_NONE
#else
	#define GRAPHICS_NONE 1
#endif

#if GRAPHICS_XNA31
	#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
	#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_XNA40
	#define UsingFrameworkNamespace using namespace Microsoft::Xna::Framework;
	#define UsingGraphicsNamespace using namespace Microsoft::Xna::Framework::Graphics;
#elif GRAPHICS_SLIMDX
	#define UsingFrameworkNamespace using namespace SlimDX;
	#define UsingGraphicsNamespace using namespace SlimDX::Direct3D9;
#elif GRAPHICS_SLIMMATH
	#define UsingFrameworkNamespace using namespace SlimMath;
	#define UsingGraphicsNamespace
#elif GRAPHICS_MOGRE
	#define UsingFrameworkNamespace using namespace Mogre;
	#define UsingGraphicsNamespace
#elif GRAPHICS_OPENTK
	#define UsingFrameworkNamespace using namespace OpenTK;
	#define UsingGraphicsNamespace using namespace OpenTK::Graphics;
#elif GRAPHICS_AXIOM
	#define UsingFrameworkNamespace using namespace Axiom::Math;
	#define UsingGraphicsNamespace
#elif GRAPHICS_NONE
	#define UsingFrameworkNamespace
	#define UsingGraphicsNamespace
#endif

#ifdef USE_INT_COLOR
	#define BtColor int
	#define BtColorToBtVector(color) new btVector3((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff)
	#define BtVectorToBtColor(color) (((int)(color.getX()*255) << 16) + ((int)(color.getY()*255) << 8) + (int)(color.getZ()*255))
#elif GRAPHICS_XNA31
	#define BtColor Microsoft::Xna::Framework::Graphics::Color
	#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_XNA40
	#define BtColor Microsoft::Xna::Framework::Color
	#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_SLIMDX
	#define BtColor Color4
	#define BtColorToBtVector(color) new btVector3(color.Red, color.Green, color.Blue)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_SLIMMATH
	#define BtColor Color3
	#define BtColorToBtVector(color) new btVector3(color.Red, color.Green, color.Blue)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_MOGRE
	#define BtColor Mogre::ColourValue
	#define BtColorToBtVector(color) new btVector3(color.r, color.g, color.b)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_OPENTK
	#define BtColor OpenTK::Graphics::Color4
	#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ(),1)
#elif GRAPHICS_AXIOM
	#define BtColor Axiom::Core::ColorEx
	#define BtColorToBtVector(color) new btVector3(color.r, color.g, color.b)
	#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_NONE
	#define BtColor Color
	#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) Color::FromArgb(color.getX(), color.getY(), color.getZ())
#endif

//#define BT_MANAGED_CODE

#pragma managed(push, off)

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#pragma managed(pop)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Math.h"

#ifndef DISABLE_SOFTBODY
#pragma managed(push, off)
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodySolvers.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#pragma managed(pop)
#endif

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

inline void* GCHandleToVoidPtr(GCHandle handle)
{
	return (GCHandle::operator System::IntPtr(handle)).ToPointer();
}

inline GCHandle VoidPtrToGCHandle(void* pointer)
{
	return GCHandle::operator GCHandle(System::IntPtr(pointer));
}

#define GetUnmanagedNullable(value) (value != nullptr ? value->UnmanagedPointer : 0)

using namespace BulletSharp;
