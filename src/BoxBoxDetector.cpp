#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BoxBoxDetector.h"
#include "BoxShape.h"

#define Native static_cast<btBoxBoxDetector*>(_native)

BoxBoxDetector::BoxBoxDetector(btBoxBoxDetector* detector)
: DiscreteCollisionDetectorInterface(detector)
{
}

BoxBoxDetector::BoxBoxDetector(BoxShape^ box1, BoxShape^ box2)
: DiscreteCollisionDetectorInterface(0)
{
	_native = ALIGNED_NEW(btBoxBoxDetector) ((btBoxShape*)box1->_native, (btBoxShape*)box2->_native);
}

BoxShape^ BoxBoxDetector::Box1::get()
{
	return dynamic_cast<BoxShape^>(CollisionShape::GetManaged((btBoxShape*)Native->m_box1));
}
void BoxBoxDetector::Box1::set(BoxShape^ value)
{
	Native->m_box1 = (btBoxShape*)value->_native;
}

BoxShape^ BoxBoxDetector::Box2::get()
{
	return dynamic_cast<BoxShape^>(CollisionShape::GetManaged((btBoxShape*)Native->m_box2));
}
void BoxBoxDetector::Box2::set(BoxShape^ value)
{
	Native->m_box2 = (btBoxShape*)value->_native;
}

#endif
