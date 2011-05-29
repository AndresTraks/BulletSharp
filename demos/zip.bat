@echo off

if exist bin goto _bin
mkdir bin
:_bin

if exist bin\SlimDX goto _bins
mkdir bin\SlimDX
:_bins

if exist bin\SlimDX\data goto _binsd
mkdir bin\SlimDX\data
:_binsd

if exist bin\SharpDX goto _binsh
mkdir bin\SharpDX
:_binsh

if exist bin\SharpDX\data goto _binshd
mkdir bin\SharpDX\data
:_binshd

if exist bin\OpenTK goto _bino
mkdir bin\OpenTK
:_bino

if exist bin goto _src
mkdir src
:_src

if exist src\SlimDX goto _srcs
mkdir src\SlimDX
:_srcs

if exist src\SharpDX goto _srcsh
mkdir src\SharpDX
:_srcsh

if exist src\OpenTK goto _srco
mkdir src\OpenTK
:_srco

if exist src\XNA goto _srcx
mkdir src\XNA
:_srcx

if exist src\XNA4 goto _srcx4
mkdir src\XNA4
:_srcx4

if exist src\Mogre goto _srcm
mkdir src\Mogre
:_srcm

copy "..\VS2008\Release SlimDX\BulletSharp.dll" bin\SlimDX\
copy "..\VS2008\Release OpenTK\BulletSharp.dll" bin\OpenTK\
copy "..\Release SharpDX\BulletSharp.dll" bin\SharpDX\


copy SlimDX\DemoFramework\bin\x86\Release\DemoFramework.dll bin\SlimDX\
rem copy SlimDX\AllBulletDemos\bin\Release\AllBulletDemos.exe bin\SlimDX\
copy SlimDX\BasicDemo\bin\x86\Release\BasicDemo.exe bin\SlimDX\
copy SlimDX\BenchmarkDemo\bin\x86\Release\BenchmarkDemo.exe bin\SlimDX\
copy SlimDX\Box2dDemo\bin\x86\Release\Box2dDemo.exe bin\SlimDX\
copy SlimDX\CcdPhysicsDemo\bin\x86\Release\CcdPhysicsDemo.exe bin\SlimDX\
copy SlimDX\ConstraintDemo\bin\x86\Release\ConstraintDemo.exe bin\SlimDX\
copy SlimDX\DistanceDemo\bin\x86\Release\DistanceDemo.exe bin\SlimDX\
copy SlimDX\GImpactTestDemo\bin\x86\Release\GImpactTestDemo.exe bin\SlimDX\
rem copy SlimDX\MultiMaterialDemo\bin\x86\Release\MultiMaterialDemo.exe bin\SlimDX\
rem copy SlimDX\OpenCLClothDemo\bin\x86\Release\OpenCLClothDemo.exe bin\SlimDX\
copy SlimDX\RagdollDemo\bin\x86\Release\RagdollDemo.exe bin\SlimDX\
copy SlimDX\SerializeDemo\bin\x86\Release\SerializeDemo.exe bin\SlimDX\
copy SlimDX\SimplestDemo\bin\x86\Release\SimplestDemo.exe bin\SlimDX\
copy SlimDX\SoftDemo\bin\x86\Release\SoftDemo.exe bin\SlimDX\
copy SlimDX\VehicleDemo\bin\x86\Release\VehicleDemo.exe bin\SlimDX\
copy SlimDX\SoftDemo\data\cube.ele bin\SlimDX\data\
copy SlimDX\SoftDemo\data\cube.node bin\SlimDX\data\

rem cmd /C svn export SlimDX\AllBulletDemos src\SlimDX\AllBulletDemos --force
cmd /C svn export SlimDX\DemoFramework src\SlimDX\DemoFramework --force
cmd /C svn export SlimDX\BasicDemo src\SlimDX\BasicDemo --force
cmd /C svn export SlimDX\BenchmarkDemo src\SlimDX\BenchmarkDemo --force
cmd /C svn export SlimDX\Box2dDemo src\SlimDX\Box2dDemo --force
cmd /C svn export SlimDX\CcdPhysicsDemo src\SlimDX\CcdPhysicsDemo --force
cmd /C svn export SlimDX\ConstraintDemo src\SlimDX\ConstraintDemo --force
cmd /C svn export SlimDX\DistanceDemo src\SlimDX\DistanceDemo --force
cmd /C svn export SlimDX\GImpactTestDemo src\SlimDX\GImpactTestDemo --force
rem cmd /C svn export SlimDX\MultiMaterialDemo src\SlimDX\MultiMaterialDemo --force
rem cmd /C svn export SlimDX\OpenCLClothDemo src\SlimDX\OpenCLClothDemo --force
cmd /C svn export SlimDX\RagdollDemo src\SlimDX\RagdollDemo --force
cmd /C svn export SlimDX\SerializeDemo src\SlimDX\SerializeDemo --force
cmd /C svn export SlimDX\SimplestDemo src\SlimDX\SimplestDemo --force
cmd /C svn export SlimDX\SoftDemo src\SlimDX\SoftDemo --force
cmd /C svn export SlimDX\VehicleDemo src\SlimDX\VehicleDemo --force


copy SharpDX\DemoFramework\bin\Release\DemoFramework.dll bin\SharpDX\
copy SharpDX\DemoFramework\bin\Release\grender.fx bin\SharpDX\
copy SharpDX\DemoFramework\bin\Release\shader.fx bin\SharpDX\
copy SharpDX\BasicDemo\bin\Release\BasicDemo.exe bin\SharpDX\
copy SharpDX\CcdPhysicsDemo\bin\Release\CcdPhysicsDemo.exe bin\SharpDX\
copy SharpDX\SoftDemo\bin\Release\SoftDemo.exe bin\SharpDX\
copy SharpDX\SoftDemo\data\cube.ele bin\SharpDX\data\
copy SharpDX\SoftDemo\data\cube.node bin\SharpDX\data\
copy SharpDX\SharpDX.D3DCompiler.dll bin\SharpDX\
copy SharpDX\SharpDX.Direct3D10.dll bin\SharpDX\
copy SharpDX\SharpDX.dll bin\SharpDX\
copy SharpDX\SharpDX.DXGI.dll bin\SharpDX\
copy SharpDX\SharpDX.Error.dll bin\SharpDX\

cmd /C svn export SharpDX\DemoFramework src\SharpDX\DemoFramework --force
cmd /C svn export SharpDX\BasicDemo src\SharpDX\BasicDemo --force
cmd /C svn export SharpDX\CcdPhysicsDemo src\SharpDX\CcdPhysicsDemo --force
cmd /C svn export SharpDX\SoftDemo src\SharpDX\SoftDemo --force


copy OpenTK\BasicDemo\bin\x86\release\BasicDemo.exe bin\OpenTK\
copy OpenTK\BasicDemo\bin\x86\release\OpenTK.dll bin\OpenTK\

cmd /C svn export OpenTK\BasicDemo src\OpenTK\BasicDemo --force
cmd /C svn export XNA\BasicDemo src\XNA\BasicDemo --force
cmd /C svn export XNA4\BasicDemo src\XNA4\BasicDemo --force
cmd /C svn export Mogre\BasicDemo src\Mogre\BasicDemo --force

"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp-demos.7z bin src
"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp-demos.zip bin src
