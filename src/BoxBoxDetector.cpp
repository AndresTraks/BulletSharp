#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BoxBoxDetector.h"
#include "BoxShape.h"

BoxBoxDetector::BoxBoxDetector(btBoxBoxDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BoxBoxDetector::BoxBoxDetector(BoxShape^ box1, BoxShape^ box2)
: DiscreteCollisionDetectorInterface(new btBoxBoxDetector(
	(btBoxShape*)box1->_unmanaged, (btBoxShape*)box2->_unmanaged))
{
}

BoxShape^ BoxBoxDetector::Box1::get()
{
	return gcnew BoxShape((btBoxShape*)UnmanagedPointer->m_box1);
}
void BoxBoxDetector::Box1::set(BoxShape^ value)
{
	UnmanagedPointer->m_box1 = (btBoxShape*)value->_unmanaged;
}

BoxShape^ BoxBoxDetector::Box2::get()
{
	return gcnew BoxShape((btBoxShape*)UnmanagedPointer->m_box2);
}
void BoxBoxDetector::Box2::set(BoxShape^ value)
{
	UnmanagedPointer->m_box2 = (btBoxShape*)value->_unmanaged;
}

btBoxBoxDetector* BoxBoxDetector::UnmanagedPointer::get()
{
	return (btBoxBoxDetector*)DiscreteCollisionDetectorInterface::UnmanagedPointer;
}

#endif
