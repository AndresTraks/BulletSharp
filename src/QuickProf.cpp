#include "StdAfx.h"

#ifndef BT_NO_PROFILE

#include "QuickProf.h"
#include "StringConv.h"

#ifdef USE_BT_CLOCK

Clock::Clock(btClock* native)
{
	_native = native;
}

Clock::~Clock()
{
	this->!Clock();
}

Clock::!Clock()
{
	delete _native;
	_native = NULL;
}

Clock::Clock()
{
	_native = new btClock();
}

Clock::Clock(Clock^ other)
{
	_native = new btClock(*other->_native);
}

Clock^ Clock::operator=(Clock^ other)
{
	return gcnew Clock(&_native->operator=(*other->_native));
}

void Clock::Reset()
{
	_native->reset();
}

unsigned long Clock::TimeMicroseconds::get()
{
	return _native->getTimeMicroseconds();
}

unsigned long Clock::TimeMilliseconds::get()
{
	return _native->getTimeMilliseconds();
}

btScalar Clock::TimeSeconds::get()
{
	return _native->getTimeSeconds();
}

#endif


BulletSharp::CProfileNode::CProfileNode(::CProfileNode* native)
{
	_native = native;
}
/*
BulletSharp::CProfileNode::CProfileNode(String^ name, BulletSharp::CProfileNode^ parent)
{
	_native = new ::CProfileNode(name->_native, parent->_native);
}
*/
void BulletSharp::CProfileNode::Call()
{
	_native->Call();
}

void BulletSharp::CProfileNode::CleanupMemory()
{
	_native->CleanupMemory();
}
/*
BulletSharp::CProfileNode^ BulletSharp::CProfileNode::GetSubNode(String^ name)
{
	return gcnew BulletSharp::CProfileNode(_native->Get_Sub_Node(name->_native));
}
*/
void BulletSharp::CProfileNode::Reset()
{
	_native->Reset();
}

bool BulletSharp::CProfileNode::Return()
{
	return _native->Return();
}

BulletSharp::CProfileNode^ BulletSharp::CProfileNode::Child::get()
{
	return gcnew BulletSharp::CProfileNode(_native->Get_Child());
}

String^ BulletSharp::CProfileNode::Name::get()
{
	return StringConv::UnmanagedToManaged(_native->Get_Name());
}

BulletSharp::CProfileNode^ BulletSharp::CProfileNode::Parent::get()
{
	return gcnew BulletSharp::CProfileNode(_native->Get_Parent());
}

BulletSharp::CProfileNode^ BulletSharp::CProfileNode::Sibling::get()
{
	return gcnew BulletSharp::CProfileNode(_native->Get_Sibling());
}

int BulletSharp::CProfileNode::TotalCalls::get()
{
	return _native->Get_Total_Calls();
}

float BulletSharp::CProfileNode::TotalTime::get()
{
	return _native->Get_Total_Time();
}

IntPtr BulletSharp::CProfileNode::UserPointer::get()
{
	return IntPtr(_native->GetUserPointer());
}
void BulletSharp::CProfileNode::UserPointer::set(IntPtr ptr)
{
	_native->SetUserPointer(ptr.ToPointer());
}


BulletSharp::CProfileIterator::CProfileIterator(::CProfileIterator* native)
{
	_native = native;
}
/*
BulletSharp::CProfileIterator::CProfileIterator()
{
	_native = new ::CProfileIterator();
}
*/
void BulletSharp::CProfileIterator::EnterChild(int index)
{
	_native->Enter_Child(index);
}
/*
void BulletSharp::CProfileIterator::EnterLargestChild()
{
	_native->Enter_Largest_Child();
}
*/
void BulletSharp::CProfileIterator::EnterParent()
{
	_native->Enter_Parent();
}

void BulletSharp::CProfileIterator::First()
{
	_native->First();
}

void BulletSharp::CProfileIterator::Next()
{
	_native->Next();
}

String^ BulletSharp::CProfileIterator::CurrentName::get()
{
	return StringConv::UnmanagedToManaged(_native->Get_Current_Name());
}

String^ BulletSharp::CProfileIterator::CurrentParentName::get()
{
	return StringConv::UnmanagedToManaged(_native->Get_Current_Parent_Name());
}

int BulletSharp::CProfileIterator::CurrentParentTotalCalls::get()
{
	return _native->Get_Current_Parent_Total_Calls();
}

float BulletSharp::CProfileIterator::CurrentParentTotalTime::get()
{
	return _native->Get_Current_Parent_Total_Time();
}

int BulletSharp::CProfileIterator::CurrentTotalCalls::get()
{
	return _native->Get_Current_Total_Calls();
}

float BulletSharp::CProfileIterator::CurrentTotalTime::get()
{
	return _native->Get_Current_Total_Time();
}

IntPtr BulletSharp::CProfileIterator::CurrentUserPointer::get()
{
	return IntPtr(_native->Get_Current_UserPointer());
}
void BulletSharp::CProfileIterator::CurrentUserPointer::set(IntPtr ptr)
{
	_native->Set_Current_UserPointer(ptr.ToPointer());
}

bool BulletSharp::CProfileIterator::IsDone::get()
{
	return _native->Is_Done();
}

bool BulletSharp::CProfileIterator::IsRoot::get()
{
	return _native->Is_Root();
}


void BulletSharp::CProfileManager::CleanupMemory()
{
	::CProfileManager::CleanupMemory();
}

void BulletSharp::CProfileManager::DumpAll()
{
	::CProfileManager::dumpAll();
}

void BulletSharp::CProfileManager::DumpRecursive(BulletSharp::CProfileIterator^ profileIterator, int spacing)
{
	::CProfileManager::dumpRecursive(profileIterator->_native, spacing);
}

void BulletSharp::CProfileManager::IncrementFrameCounter()
{
	::CProfileManager::Increment_Frame_Counter();
}

void BulletSharp::CProfileManager::ReleaseIterator(BulletSharp::CProfileIterator^ iterator)
{
	::CProfileManager::Release_Iterator(iterator->_native);
}

void BulletSharp::CProfileManager::Reset()
{
	::CProfileManager::Reset();
}
/*
void BulletSharp::CProfileManager::StartProfile(String^ name)
{
	::CProfileManager::Start_Profile(name->_native);
}
*/
void BulletSharp::CProfileManager::StopProfile()
{
	::CProfileManager::Stop_Profile();
}

int BulletSharp::CProfileManager::FrameCountSinceReset::get()
{
	return ::CProfileManager::Get_Frame_Count_Since_Reset();
}

BulletSharp::CProfileIterator^ BulletSharp::CProfileManager::Iterator::get()
{
	return gcnew BulletSharp::CProfileIterator(::CProfileManager::Get_Iterator());
}

float BulletSharp::CProfileManager::TimeSinceReset::get()
{
	return ::CProfileManager::Get_Time_Since_Reset();
}


BulletSharp::CProfileSample::CProfileSample(::CProfileSample* native)
{
	_native = native;
}
/*
BulletSharp::CProfileSample::CProfileSample(String^ name)
{
	_native = new ::CProfileSample(name->_native);
}
*/
#endif
