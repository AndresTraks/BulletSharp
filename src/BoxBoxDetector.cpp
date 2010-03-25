#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btBoxBoxDetector.h>
#pragma managed(pop)

#include "BoxBoxDetector.h"
#include "BoxShape.h"

BoxBoxDetector::BoxBoxDetector(btBoxBoxDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BoxBoxDetector::BoxBoxDetector(BoxShape^ box1, BoxShape^ box2)
: DiscreteCollisionDetectorInterface(new btBoxBoxDetector(
	box1->UnmanagedPointer, box2->UnmanagedPointer))
{
}

BoxShape^ BoxBoxDetector::Box1::get()
{
	return gcnew BoxShape(UnmanagedPointer->m_box1);
}
void BoxBoxDetector::Box1::set(BoxShape^ value)
{
	UnmanagedPointer->m_box1 = value->UnmanagedPointer;
}

BoxShape^ BoxBoxDetector::Box2::get()
{
	return gcnew BoxShape(UnmanagedPointer->m_box2);
}
void BoxBoxDetector::Box2::set(BoxShape^ value)
{
	UnmanagedPointer->m_box2 = value->UnmanagedPointer;
}

btBoxBoxDetector* BoxBoxDetector::UnmanagedPointer::get()
{
	return (btBoxBoxDetector*)DiscreteCollisionDetectorInterface::UnmanagedPointer;
}
