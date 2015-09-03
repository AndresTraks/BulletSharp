#include "StdAfx.h"

#include <LinearMath/btCpuFeatureUtility.h>
#include "CpuFeatureUtility.h"

BulletSharp::CpuFeatures CpuFeatureUtility::CpuFeatures::get()
{
	return (BulletSharp::CpuFeatures)btCpuFeatureUtility::getCpuFeatures();
}
