#include "StdAfx.h"

#include "Collections.h"
#include "CompoundShape.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

CompoundShapeChild::CompoundShapeChild(btCompoundShapeChild* compoundShapeChild)
{
	_child = compoundShapeChild;
}

CompoundShapeChild::CompoundShapeChild()
{
	_child = new btCompoundShapeChild;
}

btScalar CompoundShapeChild::ChildMargin::get()
{
	return _child->m_childMargin;
}
void CompoundShapeChild::ChildMargin::set(btScalar value)
{
	_child->m_childMargin = value;
}

CollisionShape^ CompoundShapeChild::ChildShape::get()
{
	return CollisionShape::GetManaged(_child->m_childShape);
}
void CompoundShapeChild::ChildShape::set(CollisionShape^ value)
{
	_child->m_childShape = value->_native;
}

BroadphaseNativeType CompoundShapeChild::ChildShapeType::get()
{
	return (BroadphaseNativeType)_child->m_childShapeType;
}
void CompoundShapeChild::ChildShapeType::set(BroadphaseNativeType value)
{
	_child->m_childShapeType = (int)value;
}

#ifndef DISABLE_DBVT
DbvtNode^ CompoundShapeChild::Node::get()
{
	if (_child->m_node == 0)
		return nullptr;
	return gcnew DbvtNode(_child->m_node);
}
void CompoundShapeChild::Node::set(DbvtNode^ value)
{
	_child->m_node = GetUnmanagedNullable(value);
}
#endif

Matrix CompoundShapeChild::Transform::get()
{
	return Math::BtTransformToMatrix(&_child->m_transform);
}
void CompoundShapeChild::Transform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_child->m_transform);
}

btCompoundShapeChild* CompoundShapeChild::UnmanagedPointer::get()
{
	return _child;
}
void CompoundShapeChild::UnmanagedPointer::set(btCompoundShapeChild* value)
{
	_child = value;
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

void CompoundShape::CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix principal, Vector3 inertia)
{
	pin_ptr<btScalar> massesPtr = &masses[0];
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	VECTOR3_DEF(inertia);
	
	Native->calculatePrincipalAxisTransform(massesPtr, *principalTemp, VECTOR3_USE(inertia));
	
	ALIGNED_FREE(principalTemp);
	VECTOR3_DEL(inertia);
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
	Native->removeChildShape(shape->UnmanagedPointer);
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
	btCompoundShapeChild* childList = Native->getChildList();
	if (childList == 0)
		return nullptr;
	return gcnew CompoundShapeChildArray(childList, Native->getNumChildShapes());
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
