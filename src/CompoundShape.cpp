#include "StdAfx.h"

#include "Collections.h"
#include "CompoundShape.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

CompoundShapeChild::CompoundShapeChild(btCompoundShapeChild* compoundShapeChild)
{
	_native = compoundShapeChild;
}

CompoundShapeChild::CompoundShapeChild()
{
	_native = new btCompoundShapeChild;
}

btScalar CompoundShapeChild::ChildMargin::get()
{
	return _native->m_childMargin;
}
void CompoundShapeChild::ChildMargin::set(btScalar value)
{
	_native->m_childMargin = value;
}

CollisionShape^ CompoundShapeChild::ChildShape::get()
{
	return CollisionShape::GetManaged(_native->m_childShape);
}
void CompoundShapeChild::ChildShape::set(CollisionShape^ value)
{
	_native->m_childShape = value->_native;
}

BroadphaseNativeType CompoundShapeChild::ChildShapeType::get()
{
	return (BroadphaseNativeType)_native->m_childShapeType;
}
void CompoundShapeChild::ChildShapeType::set(BroadphaseNativeType value)
{
	_native->m_childShapeType = (int)value;
}

#ifndef DISABLE_DBVT
DbvtNode^ CompoundShapeChild::Node::get()
{
	if (_native->m_node == 0)
		return nullptr;
	return gcnew DbvtNode(_native->m_node);
}
void CompoundShapeChild::Node::set(DbvtNode^ value)
{
	_native->m_node = GetUnmanagedNullable(value);
}
#endif

Matrix CompoundShapeChild::Transform::get()
{
	return Math::BtTransformToMatrix(&_native->m_transform);
}
void CompoundShapeChild::Transform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_transform);
}


#define Native (static_cast<btCompoundShape*>(_native))

CompoundShape::CompoundShape(btCompoundShape* compoundShape)
: CollisionShape(compoundShape)
{
}

CompoundShape::CompoundShape()
: CollisionShape(new btCompoundShape())
{
}

CompoundShape::CompoundShape(bool enableDynamicAabbTree)
: CollisionShape(new btCompoundShape(enableDynamicAabbTree))
{
}

void CompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	btTransform* localTransformTemp = Math::MatrixToBtTransform(localTransform);
	Native->addChildShape(*localTransformTemp, shape->_native);
	ALIGNED_FREE(localTransformTemp);
}

void CompoundShape::CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix% principal, [Out] Vector3% inertia)
{
	pin_ptr<btScalar> massesPtr = &masses[0];
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	btVector3* inertiaTemp = new btVector3;
	
	Native->calculatePrincipalAxisTransform(massesPtr, *principalTemp, *inertiaTemp);
	Math::BtTransformToMatrix(principalTemp, principal);
	inertia = Math::BtVector3ToVector3(inertiaTemp);
	
	ALIGNED_FREE(principalTemp);
	delete inertiaTemp;
}

void CompoundShape::CreateAabbTreeFromChildren()
{
	Native->createAabbTreeFromChildren();
}

CollisionShape^ CompoundShape::GetChildShape(int index)
{
	return CollisionShape::GetManaged(Native->getChildShape(index));
}

Matrix CompoundShape::GetChildTransform(int index)
{
	return Math::BtTransformToMatrix(&Native->getChildTransform(index));
}

void CompoundShape::RecalculateLocalAabb()
{
	Native->recalculateLocalAabb();
}

void CompoundShape::RemoveChildShape(CollisionShape^ shape)
{
	Native->removeChildShape(shape->_native);
}

void CompoundShape::RemoveChildShapeByIndex(int childShapeindex)
{
	Native->removeChildShapeByIndex(childShapeindex);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform, bool shouldRecalculateLocalAabb)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	Native->updateChildTransform(childIndex, *newChildTransformTemp, shouldRecalculateLocalAabb);
	ALIGNED_FREE(newChildTransformTemp);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	Native->updateChildTransform(childIndex, *newChildTransformTemp);
	ALIGNED_FREE(newChildTransformTemp);
}

CompoundShapeChildArray^ CompoundShape::ChildList::get()
{
	if (_childList == nullptr) {
		_childList = gcnew CompoundShapeChildArray(Native->getChildList(), Native->getNumChildShapes());
	}
	return _childList;
}

#ifndef DISABLE_DBVT
Dbvt^ CompoundShape::DynamicAabbTree::get()
{
	return gcnew Dbvt(Native->getDynamicAabbTree());
}
#endif

int CompoundShape::NumChildShapes::get()
{
	return Native->getNumChildShapes();
}

int CompoundShape::UpdateRevision::get()
{
	return Native->getUpdateRevision();
}
