#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "DefaultCollisionConfiguration.h"

DefaultCollisionConfiguration::DefaultCollisionConfiguration()
: CollisionConfiguration( new btDefaultCollisionConfiguration() )
{
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(int numPerturbationIterations)
{
	UnmanagedPointer->setConvexConvexMultipointIterations(numPerturbationIterations);
}

void DefaultCollisionConfiguration::SetConvexConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold)
{
	UnmanagedPointer->setConvexConvexMultipointIterations(numPerturbationIterations, minimumPointsPerturbationThreshold);
}

btDefaultCollisionConfiguration* DefaultCollisionConfiguration::UnmanagedPointer::get()
{
	return (btDefaultCollisionConfiguration*)CollisionConfiguration::UnmanagedPointer;
}
