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

	public enum class BroadphaseNativeTypes {
		BoxShape = BOX_SHAPE_PROXYTYPE,
		TriangleShape = TRIANGLE_SHAPE_PROXYTYPE,
		TetrahedralShape = TETRAHEDRAL_SHAPE_PROXYTYPE,
		ConvexTriangleMeshShape = CONVEX_TRIANGLEMESH_SHAPE_PROXYTYPE,
		ConvexHullShape = CONVEX_HULL_SHAPE_PROXYTYPE,
		ConvexPointCloudShape = CONVEX_POINT_CLOUD_SHAPE_PROXYTYPE,
		CustomPolyhedralShape = CUSTOM_POLYHEDRAL_SHAPE_TYPE,
		ImplicitConvexShapesStartHere = IMPLICIT_CONVEX_SHAPES_START_HERE,
		SphereShape = SPHERE_SHAPE_PROXYTYPE,
		MultiSphereShape = MULTI_SPHERE_SHAPE_PROXYTYPE,
		CapsuleShape = CAPSULE_SHAPE_PROXYTYPE,
		ConeShape = CONE_SHAPE_PROXYTYPE,
		ConvexShape = CONVEX_SHAPE_PROXYTYPE,
		CylinderShape = CYLINDER_SHAPE_PROXYTYPE,
		UniformScalingShape = UNIFORM_SCALING_SHAPE_PROXYTYPE,
		MinkowskiSumShape = MINKOWSKI_SUM_SHAPE_PROXYTYPE,
		MinkowskiDifferenceShape = MINKOWSKI_DIFFERENCE_SHAPE_PROXYTYPE,
		Box2dShape = BOX_2D_SHAPE_PROXYTYPE,
		Convex2dShape = CONVEX_2D_SHAPE_PROXYTYPE,
		CustomConvexShape = CUSTOM_CONVEX_SHAPE_TYPE,
		ConcaveShapesStartHere = CONCAVE_SHAPES_START_HERE,
		TriangleMeshShape = TRIANGLE_MESH_SHAPE_PROXYTYPE,
		ScaledTriangleMeshShape = SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE,
		FastConcaveMesh = FAST_CONCAVE_MESH_PROXYTYPE,
		TerrainShape = TERRAIN_SHAPE_PROXYTYPE,
		GImpactShape = GIMPACT_SHAPE_PROXYTYPE, 
		MultiMaterialTriangleMesh = MULTIMATERIAL_TRIANGLE_MESH_PROXYTYPE,
		EmptyShape = EMPTY_SHAPE_PROXYTYPE,
		StaticPlane = STATIC_PLANE_PROXYTYPE,
		CustomConcaveShape = CUSTOM_CONCAVE_SHAPE_TYPE,
		ConcaveShapesEndHere = CONCAVE_SHAPES_END_HERE,
		CompoundShape = COMPOUND_SHAPE_PROXYTYPE,
		SoftBodyShape = SOFTBODY_SHAPE_PROXYTYPE,
		HfFluidShape = HFFLUID_SHAPE_PROXYTYPE,
		HfFluidBuoyantConvexShape = HFFLUID_BUOYANT_CONVEX_SHAPE_PROXYTYPE,
		InvalidShape = INVALID_SHAPE_PROXYTYPE,
		MaxBroadphaseCollisionTypes = MAX_BROADPHASE_COLLISION_TYPES
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
