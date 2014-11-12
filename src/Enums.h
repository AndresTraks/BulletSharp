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
	public enum class AnisotropicFrictionFlags
	{
		//None = btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED,
		AnisotropicFrictionDisabled = btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED,
		AnisotropicFriction = btCollisionObject::CF_ANISOTROPIC_FRICTION,
		AnisotropicRollingFriction = btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION,
	};

	public enum class BroadphaseNativeType
	{
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
		Box2DShape = BOX_2D_SHAPE_PROXYTYPE,
		Convex2DShape = CONVEX_2D_SHAPE_PROXYTYPE,
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
		MaxBroadphaseCollisionType = MAX_BROADPHASE_COLLISION_TYPES
	};

#ifndef DISABLE_SOFTBODY
	public enum class BufferType
	{
		Cpu = btVertexBufferDescriptor::CPU_BUFFER,
		DX11 = btVertexBufferDescriptor::DX11_BUFFER,
		OpenGL = btVertexBufferDescriptor::OPENGL_BUFFER
	};
#endif

#ifndef DISABLE_MULTITHREADED
#ifdef __OPENCL_CL_H
	[Flags]
	public enum class CLCommandQueueProperties
	{
		None = 0,
		OutOfOrderExecModeEnable = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE,
		ProfilingEnable = CL_QUEUE_PROFILING_ENABLE
	};

	public enum class CLContext
	{
		ReferenceCount = CL_CONTEXT_REFERENCE_COUNT,
		NumDevices = CL_CONTEXT_NUM_DEVICES,
		Devices = CL_CONTEXT_DEVICES,
		Properties = CL_CONTEXT_PROPERTIES,
		Platform = CL_CONTEXT_PLATFORM
	};

	public enum class CLDevice
	{
		Type = CL_DEVICE_TYPE,
		VendorID = CL_DEVICE_VENDOR_ID,
		MaxComputeUnits = CL_DEVICE_MAX_COMPUTE_UNITS,
		MaxWorkItemDimensions = CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
		MaxWorkGroupSize = CL_DEVICE_MAX_WORK_GROUP_SIZE,
		MaxWorkItemSizes = CL_DEVICE_MAX_WORK_ITEM_SIZES,
		PreferredVectorWidthChar = CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
		PreferredVectorWidthShort = CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
		PreferredVectorWidthInt = CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
		PreferredVectorWidthLong = CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
		PreferredVectorWidthFloat = CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
		PreferredVectorWidthDouble = CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
		MaxClockFrequency = CL_DEVICE_MAX_CLOCK_FREQUENCY,
		AddressBits = CL_DEVICE_ADDRESS_BITS,
		MaxReadImageArgs = CL_DEVICE_MAX_READ_IMAGE_ARGS,
		MaxWriteImageArgs = CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
		MaxMemAllocSize = CL_DEVICE_MAX_MEM_ALLOC_SIZE,
		Image2DMaxWidth = CL_DEVICE_IMAGE2D_MAX_WIDTH,
		Image2DMaxHeight = CL_DEVICE_IMAGE2D_MAX_HEIGHT,
		Image3DMaxWidth = CL_DEVICE_IMAGE3D_MAX_WIDTH,
		Image3DMaxHeight = CL_DEVICE_IMAGE3D_MAX_HEIGHT,
		Image3DMaxDepth = CL_DEVICE_IMAGE3D_MAX_DEPTH,
		ImageSupport = CL_DEVICE_IMAGE_SUPPORT,
		MaxParameterSize = CL_DEVICE_MAX_PARAMETER_SIZE,
		MaxSamplers = CL_DEVICE_MAX_SAMPLERS,
		MemBaseAddrAlign = CL_DEVICE_MEM_BASE_ADDR_ALIGN,
		MinDataTypeAlignSize = CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
		SingleFPConfig = CL_DEVICE_SINGLE_FP_CONFIG,
		GlobalMemCacheType = CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
		GlobalMemCachelineSize = CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
		GlobalMemCacheSize = CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
		GlobalMemSize = CL_DEVICE_GLOBAL_MEM_SIZE,
		MaxConstantBufferSize = CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
		MaxConstantArgs = CL_DEVICE_MAX_CONSTANT_ARGS,
		LocalMemType = CL_DEVICE_LOCAL_MEM_TYPE,
		LocalMemSize = CL_DEVICE_LOCAL_MEM_SIZE,
		ErrorCorrectionSupport = CL_DEVICE_ERROR_CORRECTION_SUPPORT,
		ProfilingTimerResolution = CL_DEVICE_PROFILING_TIMER_RESOLUTION,
		EndianLittle = CL_DEVICE_ENDIAN_LITTLE,
		Available = CL_DEVICE_AVAILABLE,
		CompilerAvailable = CL_DEVICE_COMPILER_AVAILABLE,
		ExecutionCapabilities = CL_DEVICE_EXECUTION_CAPABILITIES,
		QueueProperties = CL_DEVICE_QUEUE_PROPERTIES,
		Name = CL_DEVICE_NAME,
		Vendor = CL_DEVICE_VENDOR,
		DriverVersion = CL_DRIVER_VERSION,
		Extensions = CL_DEVICE_EXTENSIONS,
		Platform = CL_DEVICE_PLATFORM,
#ifdef USE_AMD_OPENCL
		//DoubleFPConfig = CL_DEVICE_DOUBLE_FP_CONFIG,
		//HalfFPConfig = CL_DEVICE_HALF_FP_CONFIG,
		PreferredVectorWidthHalf = CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,
		HostUnifiedMemory = CL_DEVICE_HOST_UNIFIED_MEMORY,
		NativeVectorWidthChar = CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,
		NativeVectorWidthShort = CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,
		NativeVectorWidthInt = CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,
		NativeVectorWidthLong = CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,
		NativeVectorWidthFloat = CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,
		NativeVectorWidthDouble = CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,
		NativeVectorWidthHalf = CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,
		OpenCLCVersion = CL_DEVICE_OPENCL_C_VERSION,
#endif
	};

	public enum class CLDeviceLocalMemoryType
	{
		Local = CL_LOCAL,
		Global = CL_GLOBAL
	};

	[Flags]
	public enum class CLDeviceType
	{
		None = 0,
		Default = CL_DEVICE_TYPE_DEFAULT,
		Cpu = CL_DEVICE_TYPE_CPU,
		Gpu = CL_DEVICE_TYPE_GPU,
		Accelerator = CL_DEVICE_TYPE_ACCELERATOR,
#ifdef USE_MINICL
		Debug = CL_DEVICE_TYPE_DEBUG,
#endif
		All = CL_DEVICE_TYPE_ALL
	};

	public enum class CLPlatform
	{
		Profile = CL_PLATFORM_PROFILE,
		Version = CL_PLATFORM_VERSION,
		Name = CL_PLATFORM_NAME,
		Vendor = CL_PLATFORM_VENDOR,
		Extensions = CL_PLATFORM_EXTENSIONS
	};
#endif // __OPENCL_CL_H
#endif // DISABLE_MULTITHREADED

	[Flags]
	public enum class CollisionFlags
	{
		None = 0,
		StaticObject = btCollisionObject::CF_STATIC_OBJECT,
		KinematicObject = btCollisionObject::CF_KINEMATIC_OBJECT,
		NoContactResponse = btCollisionObject::CF_NO_CONTACT_RESPONSE,
		CustomMaterialCallback = btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK,
		CharacterObject = btCollisionObject::CF_CHARACTER_OBJECT,
		DisableVisualizeObject = btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
	};

	[Flags]
	public enum class CollisionObjectTypes
	{
		None = 0,
		CollisionObjectType = btCollisionObject::CO_COLLISION_OBJECT,
		RigidBodyType = btCollisionObject::CO_RIGID_BODY,
		GhostObjectType = btCollisionObject::CO_GHOST_OBJECT,
		SoftBodyType = btCollisionObject::CO_SOFT_BODY,
		HfFluidType = btCollisionObject::CO_HF_FLUID,
		UserType = btCollisionObject::CO_USER_TYPE,
		FeatherStoneLinkType = btCollisionObject::CO_FEATHERSTONE_LINK
	};

	[Flags]
	public enum class CollisionFilterGroups
	{
		None = 0,
		DefaultFilter = btBroadphaseProxy::DefaultFilter,
		StaticFilter = btBroadphaseProxy::StaticFilter,
		KinematicFilter = btBroadphaseProxy::KinematicFilter,
		DebrisFilter = btBroadphaseProxy::DebrisFilter,
		SensorTrigger = btBroadphaseProxy::SensorTrigger,
		CharacterFilter = btBroadphaseProxy::CharacterFilter,
		AllFilter = btBroadphaseProxy::AllFilter
	};

	public enum class ConstraintParam
	{
		Erp = BT_CONSTRAINT_ERP,
		StopErp = BT_CONSTRAINT_STOP_ERP,
		Cfm = BT_CONSTRAINT_CFM,
		StopCfm = BT_CONSTRAINT_STOP_CFM
	};

	public enum class ContactManifoldType
	{
		MinContactManifold = MIN_CONTACT_MANIFOLD_TYPE,
		PersistentManifold = BT_PERSISTENT_MANIFOLD_TYPE
	};

	[Flags]
	public enum class ConstraintSolverType
	{
		SequentialImpulseSolver = BT_SEQUENTIAL_IMPULSE_SOLVER,
		MlcpSolver = BT_MLCP_SOLVER,
		NncgSolver = BT_NNCG_SOLVER
	};

#ifndef DISABLE_DEBUGDRAW
	[Flags]
	public enum class DebugDrawModes
	{
		None = 0,
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
		DrawNormals = btIDebugDraw::DBG_DrawNormals,
		MaxDebugDrawMode = btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE
	};
#endif

#pragma warning(push)
#pragma warning(disable : 4482)
	[Flags]
	public enum class DispatcherFlags
	{
		None = 0,
		StaticStaticReported = btCollisionDispatcher::DispatcherFlags::CD_STATIC_STATIC_REPORTED,
		UseRelativeContactBreakingThreshold = btCollisionDispatcher::DispatcherFlags::CD_USE_RELATIVE_CONTACT_BREAKING_THRESHOLD,
		DisableContactPoolDynamicAllocation = btCollisionDispatcher::DispatcherFlags::CD_DISABLE_CONTACTPOOL_DYNAMIC_ALLOCATION
	};
#pragma warning(pop)

	public enum class DynamicsWorldType
	{
		Simple = BT_SIMPLE_DYNAMICS_WORLD,
		Discrete = BT_DISCRETE_DYNAMICS_WORLD,
		Continuous = BT_CONTINUOUS_DYNAMICS_WORLD,
		SoftRigid = BT_SOFT_RIGID_DYNAMICS_WORLD,
		Gpu = BT_GPU_DYNAMICS_WORLD
	};

	// Mix of ContactManifoldType and TypedConstraintType
	public enum class ObjectType
	{
		MinContactManifold = MIN_CONTACT_MANIFOLD_TYPE,
		PersistentManifold = BT_PERSISTENT_MANIFOLD_TYPE,
		Point2Point = POINT2POINT_CONSTRAINT_TYPE,
		Hinge = HINGE_CONSTRAINT_TYPE,
		ConeTwist = CONETWIST_CONSTRAINT_TYPE,
		D6 = D6_CONSTRAINT_TYPE,
		Slider = SLIDER_CONSTRAINT_TYPE,
		Contact = CONTACT_CONSTRAINT_TYPE,
		D6Spring = D6_SPRING_CONSTRAINT_TYPE,
		GearConstraint = GEAR_CONSTRAINT_TYPE,
		FixedConstraint = FIXED_CONSTRAINT_TYPE,
		MaxConstraint = MAX_CONSTRAINT_TYPE
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

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		public enum class PSolver
		{
			Linear = btSoftBody::ePSolver::Linear,
			Anchors = btSoftBody::ePSolver::Anchors,
			RigidContacts = btSoftBody::ePSolver::RContacts,
			SoftContacts = btSoftBody::ePSolver::SContacts,
			End = btSoftBody::ePSolver::END
		};
	};
#endif

	[Flags]
	public enum class RigidBodyFlags
	{
		None = 0,
		DisableWorldGravity = BT_DISABLE_WORLD_GRAVITY,
		EnableGyroscopicForce = BT_ENABLE_GYROPSCOPIC_FORCE
	};

	[Flags]
	public enum class SolverModes
	{
		None = 0,
		RandomizeOrder = SOLVER_RANDMIZE_ORDER,
		FrictionSeparate = SOLVER_FRICTION_SEPARATE,
		UseWarmStarting = SOLVER_USE_WARMSTARTING,
		Use2FrictionDirections = SOLVER_USE_2_FRICTION_DIRECTIONS,
		EnableFrictionDirectionCaching = SOLVER_ENABLE_FRICTION_DIRECTION_CACHING,
		DisableVelocityDependentFrictionDirection = SOLVER_DISABLE_VELOCITY_DEPENDENT_FRICTION_DIRECTION,
		CacheFriendly = SOLVER_CACHE_FRIENDLY,
		Simd = SOLVER_SIMD,
		InterleaveContactAndFrictionConstraints = SOLVER_INTERLEAVE_CONTACT_AND_FRICTION_CONSTRAINTS,
		AllowZeroLengthFrictionDirections = SOLVER_ALLOW_ZERO_LENGTH_FRICTION_DIRECTIONS
	};

#ifndef DISABLE_SOFTBODY
	public enum class SolverType
	{
		Default = btSoftBodySolver::DEFAULT_SOLVER,
		Cpu = btSoftBodySolver::CPU_SOLVER,
		CL = btSoftBodySolver::CL_SOLVER,
		CLSimd = btSoftBodySolver::CL_SIMD_SOLVER,
		DX = btSoftBodySolver::DX_SOLVER,
		DXSimd = btSoftBodySolver::DX_SIMD_SOLVER
	};
#endif

	public enum class TraversalMode
	{
		Recursive = btQuantizedBvh::TRAVERSAL_RECURSIVE,
		Stackless = ::btQuantizedBvh::TRAVERSAL_STACKLESS,
		StacklessCacheFriendly = btQuantizedBvh::TRAVERSAL_STACKLESS_CACHE_FRIENDLY
	};

#ifndef DISABLE_CONSTRAINTS
	public enum class TypedConstraintType
	{
		Point2Point = POINT2POINT_CONSTRAINT_TYPE,
		Hinge = HINGE_CONSTRAINT_TYPE,
		ConeTwist = CONETWIST_CONSTRAINT_TYPE,
		D6 = D6_CONSTRAINT_TYPE,
		Slider = SLIDER_CONSTRAINT_TYPE,
		Contact = CONTACT_CONSTRAINT_TYPE,
		D6Spring = D6_SPRING_CONSTRAINT_TYPE,
		MaxConstraint = MAX_CONSTRAINT_TYPE
	};
#endif

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		[Flags]
		public enum class VSolver
		{
			Linear = btSoftBody::eVSolver::Linear,
			End = btSoftBody::eVSolver::END
		};
	};
#endif

#ifndef DISABLE_MULTITHREADED
	public enum class Win32ThreadFunc
	{
		ProcessCollisionTask,
		SolverThreadFunc
	};

	public enum class Win32LSMemorySetupFunc
	{
		CreateCollisionLocalStoreMemory,
		SolverLSMemoryFunc
	};
#endif

};
