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
	_child->m_childShape = value->_unmanaged;
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


#define Unmanaged (static_cast<btCompoundShape*>(_unmanaged))

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
	Unmanaged->addChildShape(*localTransformTemp, shape->_unmanaged);
	delete localTransformTemp;
}

void CompoundShape::CalculatePrincipalAxisTransform(array<btScalar>^ masses, Matrix principal, Vector3 inertia)
{
	pin_ptr<btScalar> massesPtr = &masses[0];
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	VECTOR3_DEF(inertia);
	
	Unmanaged->calculatePrincipalAxisTransform(massesPtr, *principalTemp, VECTOR3_USE(inertia));
	
	delete principalTemp;
	VECTOR3_DEL(inertia);
}

void CompoundShape::CreateAabbTreeFromChildren()
{
	Unmanaged->createAabbTreeFromChildren();
}

CollisionShape^ CompoundShape::GetChildShape(int index)
{
	return CollisionShape::GetManaged(Unmanaged->getChildShape(index));
}

Matrix CompoundShape::GetChildTransform(int index)
{
	return Math::BtTransformToMatrix(&Unmanaged->getChildTransform(index));
}

void CompoundShape::RecalculateLocalAabb()
{
	Unmanaged->recalculateLocalAabb();
}

void CompoundShape::RemoveChildShape(CollisionShape^ shape)
{
	Unmanaged->removeChildShape(shape->UnmanagedPointer);
}

void CompoundShape::RemoveChildShapeByIndex(int childShapeindex)
{
	Unmanaged->removeChildShapeByIndex(childShapeindex);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform, bool shouldRecalculateLocalAabb)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	Unmanaged->updateChildTransform(childIndex, *newChildTransformTemp, shouldRecalculateLocalAabb);
	delete newChildTransformTemp;
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	Unmanaged->updateChildTransform(childIndex, *newChildTransformTemp);
	delete newChildTransformTemp;
}

CompoundShapeChildArray^ CompoundShape::ChildList::get()
{
	btCompoundShapeChild* childList = Unmanaged->getChildList();
	if (childList == 0)
		return nullptr;
	return gcnew CompoundShapeChildArray(childList, Unmanaged->getNumChildShapes());
}

#ifndef DISABLE_DBVT
Dbvt^ CompoundShape::DynamicAabbTree::get()
{
	return gcnew Dbvt(UnmanagedPointer->getDynamicAabbTree());
}
#endif

int CompoundShape::NumChildShapes::get()
{
	return Unmanaged->getNumChildShapes();
}

int CompoundShape::UpdateRevision::get()
{
	return Unmanaged->getUpdateRevision();
}

btCompoundShape* CompoundShape::UnmanagedPointer::get()
{
	return (btCompoundShape*)CollisionShape::UnmanagedPointer;
}
