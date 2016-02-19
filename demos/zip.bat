@echo off

if exist bin goto _bin
mkdir bin
goto _bin2
:_bin
rd /s /q bin
:_bin2

if exist bin\data goto _bind
mkdir bin\data
:_bind

if exist src goto _src
mkdir src
goto _src2
:_src
rd /s /q src
:_src2

copy "..\Release Generic\BulletSharp.dll" bin\

copy Generic\bin\Release\BasicDemo.exe bin\
copy Generic\bin\Release\BenchmarkDemo.exe bin\
copy Generic\bin\Release\Box2DDemo.exe bin\
copy Generic\bin\Release\BspDemo.exe bin\
copy Generic\bin\Release\BulletXmlImportDemo.exe bin\
copy Generic\bin\Release\CcdPhysicsDemo.exe bin\
copy Generic\bin\Release\CharacterDemo.exe bin\
copy Generic\bin\Release\CollisionFeedbackDemo.exe bin\
copy Generic\bin\Release\CollisionInterfaceDemo.exe bin\
copy Generic\bin\Release\ConcaveConvexCastDemo.exe bin\
copy Generic\bin\Release\ConcaveRaycastDemo.exe bin\
copy Generic\bin\Release\ConstraintDemo.exe bin\
copy Generic\bin\Release\ConvexDecompositionDemo.exe bin\
copy Generic\bin\Release\DistanceDemo.exe bin\
copy Generic\bin\Release\FeatherStoneDemo.exe bin\
copy Generic\bin\Release\GImpactTestDemo.exe bin\
copy Generic\bin\Release\MotorDemo.exe bin\
copy Generic\bin\Release\RagdollDemo.exe bin\
copy Generic\bin\Release\RollingFrictionDemo.exe bin\
copy Generic\bin\Release\SerializeDemo.exe bin\
copy Generic\bin\Release\SoftDemo.exe bin\
copy Generic\bin\Release\VehicleDemo.exe bin\

copy Generic\bin\Release\data\BspDemo.bsp bin\data\
copy Generic\bin\Release\data\file.obj bin\data\
copy Generic\bin\Release\data\cube.ele bin\data\
copy Generic\bin\Release\data\cube.node bin\data\
copy Generic\bin\Release\data\bullet_basic.xml bin\data\
copy Generic\bin\Release\testFile.bullet bin\
rem copy Generic\bin\Release\data\heightfield128x128.raw bin\data\

copy Generic\bin\Release\DemoFramework.dll bin\
copy Generic\bin\Release\DemoFramework.OpenTK.dll bin\
copy Generic\bin\Release\DemoFramework.SharpDX.dll bin\
copy Generic\bin\Release\DemoFramework.SharpDX11.dll bin\
copy Generic\bin\Release\DemoFramework.SlimDX.dll bin\
copy Generic\bin\Release\DemoFramework.MonoGame.dll bin\

copy Generic\bin\Release\OpenTK.dll bin\
copy Generic\bin\Release\OpenTK.GLControl.dll bin\
copy Generic\bin\Release\SharpDX.dll bin\
copy Generic\bin\Release\SharpDX.D3DCompiler.dll bin\
copy Generic\bin\Release\SharpDX.Direct2D1.dll bin\
copy Generic\bin\Release\SharpDX.Direct3D10.dll bin\
copy Generic\bin\Release\SharpDX.Direct3D11.dll bin\
copy Generic\bin\Release\SharpDX.Direct3D11.Effects.dll bin\
copy Generic\bin\Release\SharpDX.DXGI.dll bin\
copy Generic\bin\Release\sharpdx_direct3d11_effects_x64.dll bin\
copy Generic\bin\Release\sharpdx_direct3d11_effects_x86.dll bin\

cmd /C git clone https://github.com/AndresTraks/BulletSharp.git repo
move repo\demos\Generic src
rmdir /s /q repo

"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp-demos.zip bin src
