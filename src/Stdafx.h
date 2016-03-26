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
//#define DISABLE_FEATHERSTONE
//#define DISABLE_GEOMETRY_UTIL
//#define DISABLE_GIMPACT
//#define DISABLE_HACD
//#define DISABLE_INTERNAL
//#define DISABLE_INTERNAL_EDGE_UTILITY
//#define DISABLE_MLCP
//#define DISABLE_SERIALIZE
//#define DISABLE_SOFTBODY
//#define DISABLE_UNCOMMON
//#define DISABLE_VEHICLE


// When using CMake to compile Bullet and USE_DOUBLE_PRECISION is specified,
// then this setting isn't applied to BulletSharp automatically.
// In this case, uncomment this line:
//#define BT_USE_DOUBLE_PRECISION


// This makes ManifoldPoint.ContactAdded, PersistentManifold.ContactProcessed and PersistentManifold.ContactDestroyed
// events instead of delegate properties
#define BT_CALLBACKS_ARE_EVENTS


#if GRAPHICS_MOGRE
#if _DEBUG
#using <Mogre_d.dll>
#else
#using <Mogre.dll>
using namespace Mogre;
#endif
#elif GRAPHICS_MONOGAME
using namespace Microsoft::Xna::Framework;
#elif GRAPHICS_NUMERICS
using namespace System::Numerics;
#elif GRAPHICS_OPENTK
using namespace OpenTK;
#elif GRAPHICS_SLIMDX
#if WIN32
#using <x86/SlimDX.dll>
#elif WIN64
#using <x64/SlimDX.dll>
#endif
using namespace SlimDX;
#elif GRAPHICS_SHARPDX
using namespace SharpDX;
#elif GRAPHICS_GENERIC
#else
#define GRAPHICS_GENERIC 1
#endif


#ifdef USE_INT_COLOR
#define BtColor int
#define BtColorToBtVector(color) new btVector3((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff)
#define BtVectorToBtColor(color) (((int)(color.getX()*255) << 16) + ((int)(color.getY()*255) << 8) + (int)(color.getZ()*255))
#elif GRAPHICS_MOGRE
#define BtColor Mogre::ColourValue
#define BtColorToBtVector(color) new btVector3(color.r, color.g, color.b)
#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_MONOGAME
#define BtColor Microsoft::Xna::Framework::Color
#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
#define BtVectorToBtColor(color) BtColor((float)color.getX(), (float)color.getY(), (float)color.getZ()) // cast for DP build
#elif GRAPHICS_NUMERICS
using namespace System::Drawing;
#define BtColor Color
#define BtColorToBtVector(color) new btVector3(color.R / btScalar(255.0), color.G / btScalar(255.0), color.B / btScalar(255.0))
#define BtVectorToBtColor(color) Color::FromArgb(0, (int)(color.getX() * btScalar(255.0)), (int)(color.getY() * btScalar(255.0)), (int)(color.getZ() * btScalar(255.0)))
#elif GRAPHICS_OPENTK
#define BtColor OpenTK::Graphics::Color4
#define BtColorToBtVector(color) new btVector3(color.R, color.G, color.B)
#define BtVectorToBtColor(color) BtColor((float)color.getX(), (float)color.getY(), (float)color.getZ(), 1) // cast for DP build
#elif GRAPHICS_SLIMDX
#define BtColor Color4
#define BtColorToBtVector(color) new btVector3(color.Red, color.Green, color.Blue)
#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_SHARPDX
#define BtColor Color3
#define BtColorToBtVector(color) new btVector3(color.Red, color.Green, color.Blue)
#define BtVectorToBtColor(color) BtColor(color.getX(), color.getY(), color.getZ())
#elif GRAPHICS_GENERIC
using namespace System::Drawing;
#define BtColor Color
#define BtColorToBtVector(color) new btVector3(color.R / btScalar(255.0), color.G / btScalar(255.0), color.B / btScalar(255.0))
#define BtVectorToBtColor(color) Color::FromArgb(0, (int)(color.getX() * btScalar(255.0)), (int)(color.getY() * btScalar(255.0)), (int)(color.getZ() * btScalar(255.0)))
#endif

//#define BT_MANAGED_CODE

#pragma managed(push, off)

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#pragma managed(pop)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
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
#include <BulletCollision/CollisionShapes/btConvexPolyhedron.h>
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
//#include <BulletDynamics/MLCPSolvers/btLemkeSolver.h>
#endif

#ifndef DISABLE_COLLISION_ALGORITHMS
#include <BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h>
#endif

#ifndef DISABLE_CONSTRAINTS
#include <BulletDynamics/ConstraintSolver/btContactConstraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.h>
#include <BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.h>
#endif

#ifndef DISABLE_FEATHERSTONE
#include <BulletDynamics/Featherstone/btMultiBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointMotor.h>
#include <BulletDynamics/Featherstone/btMultiBodyLink.h>
#include <BulletDynamics/Featherstone/btMultiBodyLinkCollider.h>
#include <BulletDynamics/Featherstone/btMultiBodyPoint2Point.h>
#include <BulletDynamics/Featherstone/btMultiBodySolverConstraint.h>
#endif

#ifndef DISABLE_GEOMETRY_UTIL
#include <LinearMath/btGeometryUtil.h>
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

#ifndef DISABLE_HACD
#if _DEBUG
#pragma comment(lib, "HACD_Debug.lib")
#else
#pragma comment(lib, "HACD_MinSizeRel.lib")
#endif
#include <hacdHACD.h>
#endif

#ifndef DISABLE_MLCP
#include <BulletDynamics/MLCPSolvers/btDantzigSolver.h>
#include <BulletDynamics/MLCPSolvers/btMLCPSolver.h>
#include <BulletDynamics/MLCPSolvers/btMLCPSolverInterface.h>
#endif

#ifndef DISABLE_SERIALIZE
#if _DEBUG
#pragma comment(lib, "BulletWorldImporter_Debug.lib")
#pragma comment(lib, "BulletXmlWorldImporter_Debug.lib")
#pragma comment(lib, "BulletFileLoader_Debug.lib")
#else
#pragma comment(lib, "BulletWorldImporter_MinSizeRel.lib")
#pragma comment(lib, "BulletXmlWorldImporter_MinSizeRel.lib")
#pragma comment(lib, "BulletFileLoader_MinSizeRel.lib")
#endif
#ifdef DISABLE_GIMPACT
#include <BulletCollision/GImpact/btGImpactShape.h>
#endif
#include <..\Extras\Serialize\BulletWorldImporter\btBulletWorldImporter.h>
#include <..\Extras\Serialize\BulletXmlWorldImporter\btBulletXmlWorldImporter.h>
#endif

#ifndef DISABLE_SOFTBODY
#if _DEBUG
#pragma comment(lib, "BulletSoftBody_Debug.lib")
#else
#pragma comment(lib, "BulletSoftBody_MinSizeRel.lib")
#endif
#include <BulletSoftBody/btDefaultSoftBodySolver.h>
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

#ifndef DISABLE_INTERNAL_EDGE_UTILITY
#include "BulletCollision/CollisionDispatch/btInternalEdgeUtility.h"
#endif

#pragma managed(pop)


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;
using namespace System::Security;

#include "Math.h"
#include "Enums.h"
#include "ITrackingDisposable.h"

inline void* GCHandleToVoidPtr(GCHandle handle)
{
	return GCHandle::ToIntPtr(handle).ToPointer();
}

inline GCHandle VoidPtrToGCHandle(void* pointer)
{
	return GCHandle::FromIntPtr(System::IntPtr(pointer));
}

#define GetUnmanagedNullable(value) (value != nullptr ? value->_native : 0)

#define ReturnCachedObject(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->_native == unmanagedPtr) \
	return managedObj; \
	managedObj = type::GetManaged(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectGcnew(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->_native == unmanagedPtr) \
	return managedObj; \
	managedObj = gcnew type(unmanagedPtr); \
	return managedObj; }

#define ReturnCachedObjectGcnewNullable(type, managedObj, unmanagedPtr) { \
	if (managedObj != nullptr && managedObj->_native == unmanagedPtr) \
	return managedObj; \
	if (unmanagedPtr == 0) \
	return nullptr; \
	managedObj = gcnew type(unmanagedPtr); \
	return managedObj; }

#define ALIGNED_NEW_FORCE(targetClass) new (btAlignedAlloc(sizeof(targetClass), 16)) targetClass
#define ALIGNED_FREE_FORCE(target) btAlignedFree(target)

#if 1//defined(BT_USE_SIMD_VECTOR3) && defined(BT_USE_SSE_IN_API) && defined(BT_USE_SSE)
#define ALIGNED_NEW(targetClass) ALIGNED_NEW_FORCE(targetClass)
#define ALIGNED_FREE(target) ALIGNED_FREE_FORCE(target)
#else
#define ALIGNED_NEW(targetClass) new targetClass
#define ALIGNED_FREE(target) delete target
#endif

using namespace BulletSharp;
