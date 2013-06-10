#include "StdAfx.h"

#ifndef DISABLE_BVH

#include "OptimizedBvh.h"
#include "QuantizedBvh.h"

QuantizedBvh::QuantizedBvh(btQuantizedBvh* bvh)
{
	_native = bvh;
}

QuantizedBvh^ QuantizedBvh::GetManaged(btQuantizedBvh* quantizedBvh)
{
	if (quantizedBvh == 0) {
		return nullptr;
	}

	btOptimizedBvh* optimizedBvh = dynamic_cast<btOptimizedBvh*>(quantizedBvh);
	if (optimizedBvh) {
		return gcnew OptimizedBvh(optimizedBvh);
	}

	return gcnew QuantizedBvh(quantizedBvh);
}

QuantizedBvh::QuantizedBvh()
{
	_native = new btQuantizedBvh();
}

QuantizedBvh::~QuantizedBvh()
{
	this->!QuantizedBvh();
}

QuantizedBvh::!QuantizedBvh()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

void QuantizedBvh::BuildInternal()
{
	_native->buildInternal();
}

#ifndef DISABLE_SERIALIZE
unsigned int QuantizedBvh::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}

unsigned int QuantizedBvh::AlignmentSerializationPadding::get()
{
	return btQuantizedBvh::getAlignmentSerializationPadding();
}
#endif

bool QuantizedBvh::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
