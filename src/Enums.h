#pragma once

namespace BulletSharp
{
	public enum class ActivationState
	{
		ActiveTag = ACTIVE_TAG,
		IslandSleeping = ISLAND_SLEEPING,
		WantsDeactivation = WANTS_DEACTIVATION,
		DisableDeactivation = DISABLE_DEACTIVATION,
		DisableSimulation = DISABLE_SIMULATION
	};

	[Flags]
	public enum class CollisionFilterGroups
	{
		DefaultFilter = btBroadphaseProxy::DefaultFilter,
		StaticFilter = btBroadphaseProxy::StaticFilter,
		KinematicFilter = btBroadphaseProxy::KinematicFilter,
		DebrisFilter = btBroadphaseProxy::DebrisFilter,
		SensorTrigger = btBroadphaseProxy::SensorTrigger,
		CharacterFilter = btBroadphaseProxy::CharacterFilter,
		AllFilter = btBroadphaseProxy::AllFilter
	};

	public enum class ConstraintParams
	{
		Erp = BT_CONSTRAINT_ERP,
		StopErp = BT_CONSTRAINT_STOP_ERP,
		Cfm = BT_CONSTRAINT_CFM,
		StopCfm = BT_CONSTRAINT_STOP_CFM
	};

	[Flags]
	public enum class DebugDrawModes
	{
		NoDebug = btIDebugDraw::DBG_NoDebug,
		DrawWireframe = btIDebugDraw::DBG_DrawWireframe,
		DrawAabb = btIDebugDraw::DBG_DrawAabb,
		DrawFeaturesText = btIDebugDraw::DBG_DrawFeaturesText,
		DrawContactPoints = btIDebugDraw::DBG_DrawContactPoints,
		NoDeactivation = btIDebugDraw::DBG_NoDeactivation,
		NoHelpText = btIDebugDraw::DBG_NoHelpText,
		DrawText = btIDebugDraw::DBG_DrawText,
		ProfileTimings = btIDebugDraw::DBG_ProfileTimings,
		EnableSatComparison = btIDebugDraw::DBG_EnableSatComparison,
		DisableBulletLCP = btIDebugDraw::DBG_DisableBulletLCP,
		EnableCCD = btIDebugDraw::DBG_EnableCCD,
		DrawConstraints = btIDebugDraw::DBG_DrawConstraints,
		DrawConstraintLimits = btIDebugDraw::DBG_DrawConstraintLimits,
		FastWireframe = btIDebugDraw::DBG_FastWireframe,
		MaxDebugDrawMode = btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE
	};

	public enum class PhyScalarType
	{
		PhyFloat = PHY_FLOAT,
		PhyDouble = PHY_DOUBLE,
		PhyInteger = PHY_INTEGER,
		PhyShort = PHY_SHORT,
		PhyFixedPoint88 = PHY_FIXEDPOINT88,
		PhyUChar = PHY_UCHAR
	};

	public enum class TypedConstraintType
	{
		Point2Point = POINT2POINT_CONSTRAINT_TYPE,
		Hinge = HINGE_CONSTRAINT_TYPE,
		ConeTwist = CONETWIST_CONSTRAINT_TYPE,
		D6 = D6_CONSTRAINT_TYPE,
		Slider = SLIDER_CONSTRAINT_TYPE,
		Contact = CONTACT_CONSTRAINT_TYPE
	};
};
