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
//#define DISABLE_UNCOMMON
#define DISABLE_VECTORMATH_AOS
//#define DISABLE_VEHICLE


// When using CMake to compile Bullet and double precision is specified,
// then this setting isn't applied to BulletSharp automatically.
// In this case, uncomment this line:
//#define BT_USE_DOUBLE_PRECISION


// Choose one of these for CL
#define USE_MINICL
//#define USE_AMD_OPENCL
//#define USE_NVIDIA_OPENCL


#if GRAPHICS_XNA31
#using <Microsoft.Xna.Framework.dll>
using namespace Microsoft::Xna::Framework;
#elif GRAPHICS_XNA40
#using <Microsoft.Xna.Framework.dll>
using namespace Microsoft::Xna::Framework;
#elif GRAPHICS_SLIMDX
#if WIN32
#using <x86/SlimDX.dll>
#elif WIN64
#using <x64/SlimDX.dll>
#endif
using namespace SlimDX;
#elif GRAPHICS_SHARPDX
#using <SharpDX.dll>
using namespace SharpDX;
#elif GRAPHICS_SLIMMATH
#using <SlimMath.dll>
using namespace SlimMath;
#elif GRAPHICS_MOGRE
#if _DEBUG
#using <Mogre_d.dll>
#else
#using <Mogre.dll>
using namespace Mogre;
#endif
#elif GRAPHICS_OPENTK
#using <OpenTK.dll>
using namespace OpenTK;
#elif GRAPHICS_AXIOM
#using <Axiom.dll>
using namespace Axiom::Math;
#elif GRAPHICS_WAPICODEPACK
#if WIN32
#using <x86/Microsoft.WindowsAPICodePack.DirectX.dll>
#else
#using <x64/Microsoft.WindowsAPICodePack.DirectX.dll>
#endif
using namespace Microsoft::WindowsAPICodePack::DirectX::Direct3D;
#elif GRAPHICS_NONE
#else
#define GRAPHICS_NONE 1
#endif


#ifdef USE_INT_COLOR
#define BtColor int
#define BtColorToBtVector(color) new btVector3((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff)
#define BtVectorToBtColor(color) (((int)(color.getX()*255) << 16) + ((int)(color.getY()*255) << 8) + (int)(color.getZ()*255))
#elif GRAPHICS_XNA31
#define BtColor Microsoft::Xna::Framework::Graphics::Color
#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
#define BtVectorToBtColor(color) BtColor((float)color.getX(), (float)color.getY(), (float)color.getZ()) // cast for DP build
#elif GRAPHICS_XNA40
#define BtColor Microsoft::Xna::Framework::Color
#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
#define BtVectorToBtColor(color) BtColor((float)color.getX(), (float)color.getY(), (float)color.getZ()) // cast for DP build
#elif GRAPHICS_SLIMDX
#define BtColor Color4
#define BtColorToBtVector(color) new btVector3(color.Red, color.Green, color.Blue)
#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_SHARPDX
#define BtColor Color3
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
#elif GRAPHICS_WAPICODEPACK
#define BtColor Color
#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
#define BtVectorToBtColor(color) Color::FromArgb(color.getX(), color.getY(), color.getZ())
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
#include <msclr/auto_gcroot.h>
#include <stdio.h>
#include <vcclr.h>


// Bullet includes
#pragma managed(push, off)

#ifndef DISABLE_UNCOMMON
#include <BulletCollision/CollisionDispatch/btBoxBoxDetector.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>
#include <BulletCollision/CollisionDispatch/btUnionFind.h>
#include <BulletCollision/CollisionDispatch/SphereTriangleDetector.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#include <BulletCollision/CollisionShapes/btConvexPointCloudShape.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletCollision/CollisionShapes/btMaterial.h>
#include <BulletCollision/CollisionShapes/btMinkowskiSumShape.h>
#include <BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <BulletCollision/CollisionShapes/btTriangleBuffer.h>
#include <BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h>
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#include <LinearMath/btPoolAllocator.h>
#include <BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkConvexCast.h>
#include <BulletCollision/NarrowPhaseCollision/btConvexCast.h>
#include <BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>
#include <BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h>
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>
#include <BulletCollision/NarrowPhaseCollision/btSimplexSolverInterface.h>
//#include <BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#endif

#ifndef DISABLE_COLLISION_ALGORITHMS
#include <BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h>
#endif

#ifndef DISABLE_CONSTRAINTS
#include <BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.h>
#endif

#ifndef DISABLE_GIMPACT
#include <BulletCollision/Gimpact/btBoxCollision.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/Gimpact/btTriangleShapeEx.h>
#ifndef DISABLE_BVH
#include <BulletCollision/Gimpact/btGImpactBvh.h>
#include <BulletCollision/Gimpact/btGImpactQuantizedBvh.h>
#endif
#ifndef DISABLE_COLLISION_ALGORITHMS
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#endif
#ifdef DISABLE_UNCOMMON
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#endif
#endif

#if defined(USE_MINICL)
#include <MiniCL/cl.h>
#pragma comment(lib, "MiniCL.lib")
#pragma comment(lib, "BulletSoftBodySolvers_OpenCL_Mini.lib")
#elif defined(USE_AMD_OPENCL)
#include <CL/cl.h>
#pragma comment(lib, "OpenCL.lib")
#pragma comment(lib, "BulletSoftBodySolvers_OpenCL_AMD.lib")
#elif defined(USE_NVIDIA_OPENCL)
#include <CL/cl.h>
#pragma comment(lib, "OpenCL.lib")
#pragma comment(lib, "BulletSoftBodySolvers_OpenCL_NVidia.lib")
#endif

#ifndef DISABLE_MULTITHREADED
#define __BT_SKIP_UINT64_H 1
#include <BulletMultiThreaded/btParallelConstraintSolver.h>
#include <BulletMultiThreaded/btThreadSupportInterface.h>
#include <BulletMultiThreaded/SpuGatheringCollisionDispatcher.h>
#include <BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h>
#include <BulletMultiThreaded/Win32ThreadSupport.h>
#ifndef DISABLE_SOFTBODY
#ifdef __OPENCL_CL_H
#include <BulletMultiThreaded/GpuSoftBodySolvers/CPU/btSoftBodySolver_CPU.h>
#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#endif
#endif
#endif

#ifndef DISABLE_SERIALIZE
#ifdef DISABLE_GIMPACT
#include <BulletCollision/GImpact/btGImpactShape.h>
#endif
#include <..\Extras\Serialize\BulletWorldImporter\btBulletWorldImporter.h>
#endif

#ifndef DISABLE_SOFTBODY
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodyHelpers.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftBodySolvers.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#include <BulletSoftBody/btSparseSdf.h>
#ifndef DISABLE_COLLISION_ALGORITHMS
#include <BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.h>
#endif
#endif

#pragma managed(pop)


using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

#include "Math.h"
#include "Enums.h"

inline void* GCHandleToVoidPtr(GCHandle handle)
{
	return (GCHandle::operator System::IntPtr(handle)).ToPointer();
}

inline GCHandle VoidPtrToGCHandle(void* pointer)
{
	return GCHandle::operator GCHandle(System::IntPtr(pointer));
}

#define GetUnmanagedNullable(value) (value != nullptr ? value->UnmanagedPointer : 0)

#define ReturnCachedObject(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->UnmanagedPointer == unmanagedPtr) \
	return managedObj; \
	managedObj = gcnew type(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectNullable(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->UnmanagedPointer == unmanagedPtr) \
	return managedObj; \
	if (unmanagedPtr == 0) \
	return nullptr; \
	managedObj = gcnew type(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectUpcast(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->UnmanagedPointer == unmanagedPtr) \
	return managedObj; \
	managedObj = type::Upcast(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectUpcastNullable(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->UnmanagedPointer == unmanagedPtr) \
	return managedObj; \
	if (unmanagedPtr == 0) \
	return nullptr; \
	managedObj = type::Upcast(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectUpcastNullableCastTo(type, castTo, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->UnmanagedPointer == unmanagedPtr) \
	return managedObj; \
	if (unmanagedPtr == 0) \
	return nullptr; \
	managedObj = (castTo^)type::Upcast(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectStatic(type, managedObj, unmanagedPtr, param) { \
	if (managedObj == nullptr) \
	managedObj = gcnew type(unmanagedPtr, param); \
	return managedObj; }

using namespace BulletSharp;
