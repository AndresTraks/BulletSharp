#include "StdAfx.h"

#include "CompoundShape.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

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
	return gcnew CollisionShape(_child->m_childShape);
}
void CompoundShapeChild::ChildShape::set(CollisionShape^ value)
{
	_child->m_childShape = value->UnmanagedPointer;
}

int CompoundShapeChild::ChildShapeType::get()
{
	return _child->m_childShapeType;
}
void CompoundShapeChild::ChildShapeType::set(int value)
{
	_child->m_childShapeType = value;
}

#ifndef DISABLE_DBVT
DbvtNode^ CompoundShapeChild::Node::get()
{
	return gcnew DbvtNode(_child->m_node);
}
void CompoundShapeChild::Node::set(DbvtNode^ value)
{
	_child->m_node = value->UnmanagedPointer;
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
	UnmanagedPointer->addChildShape(*localTransformTemp, shape->UnmanagedPointer);
	delete localTransformTemp;
}

CollisionShape^ CompoundShape::GetChildShape(int index)
{
	return gcnew CollisionShape(UnmanagedPointer->getChildShape(index));
}

Matrix CompoundShape::GetChildTransform(int index)
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getChildTransform(index));
}

void CompoundShape::RecalculateLocalAabb()
{
	UnmanagedPointer->recalculateLocalAabb();
}

void CompoundShape::RemoveChildShape(CollisionShape^ shape)
{
	UnmanagedPointer->removeChildShape(shape->UnmanagedPointer);
}

void CompoundShape::RemoveChildShapeByIndex(int childShapeindex)
{
	UnmanagedPointer->removeChildShapeByIndex(childShapeindex);
}

void CompoundShape::UpdateChildTransform(int childIndex, Matrix newChildTransform)
{
	btTransform* newChildTransformTemp = Math::MatrixToBtTransform(newChildTransform);
	UnmanagedPointer->updateChildTransform(childIndex, *newChildTransformTemp);
	delete newChildTransformTemp;
}

#ifndef DISABLE_DBVT
Dbvt^ CompoundShape::DynamicAabbTree::get()
{
	return gcnew Dbvt(UnmanagedPointer->getDynamicAabbTree());
}
#endif

int CompoundShape::NumChildShapes::get()
{
	return UnmanagedPointer->getNumChildShapes();
}

int CompoundShape::UpdateRevision::get()
{
	return UnmanagedPointer->getUpdateRevision();
}

btCompoundShape* CompoundShape::UnmanagedPointer::get()
{
	return (btCompoundShape*)CollisionShape::UnmanagedPointer;
}
