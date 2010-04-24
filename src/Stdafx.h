// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

//#define DISABLE_COLLISION_ALGORITHMS
//#define DISABLE_CONSTRAINTS
#define DISABLE_DBVT
//#define DISABLE_DEBUGDRAW
#define DISABLE_SERIALIZE
//#define DISABLE_SOFTBODY
//#define DISABLE_VEHICLE

#if GRAPHICS_XNA31
	#using <Microsoft.Xna.Framework.dll>
#elif GRAPHICS_SLIMDX
#if WIN32
	#using <x86/SlimDX.dll>
#elif WIN64
	#using <x64/SlimDX.dll>
#endif
#elif GRAPHICS_MOGRE
	#using <Mogre.dll>
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

	#define BtColor Microsoft::Xna::Framework::Graphics::Color
	#define BtColorToBtVector(color) *new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) BtColor(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_SLIMDX
	#define UsingFrameworkNamespace using namespace SlimDX;
	#define UsingGraphicsNamespace using namespace SlimDX::Direct3D9;

	#define BtColor Color4
	#define BtColorToBtVector(color) *new btVector3(color.Red, color.Green, color.Blue)
	#define BtVectorToBtColor(color) BtColor(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_MOGRE
	#define UsingFrameworkNamespace using namespace Mogre;
	#define UsingGraphicsNamespace

	#define BtColor Mogre::ColourValue
	#define BtColorToBtVector(color) *new btVector3(color.r, color.g, color.b)
	#define BtVectorToBtColor(color) BtColor(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_OPENTK
	#define UsingFrameworkNamespace using namespace OpenTK;
	#define UsingGraphicsNamespace using namespace OpenTK::Graphics;

	#define BtColor OpenTK::Graphics::Color4
	#define BtColorToBtVector(color) *new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) BtColor(color.getX(),color.getY(),color.getZ(),1)
#elif GRAPHICS_AXIOM
	#define UsingFrameworkNamespace using namespace Axiom::Math;
	#define UsingGraphicsNamespace

	#define BtColor Axiom::Core::ColorEx
	#define BtColorToBtVector(color) *new btVector3(color.r, color.g, color.b)
	#define BtVectorToBtColor(color) BtColor(color.getX(),color.getY(),color.getZ())
#elif GRAPHICS_NONE
	#define UsingFrameworkNamespace
	#define UsingGraphicsNamespace

	#define BtColor Color
	#define BtColorToBtVector(color) *new btVector3(color.R, color.G, color.B)
	#define BtVectorToBtColor(color) Color::FromArgb(255, (int)(color.getX()*255), (int)(color.getY()*255), (int)(color.getY()*255))
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
