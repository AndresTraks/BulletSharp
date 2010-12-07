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

if exist bin goto _src
mkdir src
:_src

if exist src\SlimDX goto _srcs
mkdir src\SlimDX
:_srcs

copy "..\Release SlimDX\BulletSharp.dll" bin\SlimDX\
copy SlimDX\DemoFramework\bin\x86\Release\DemoFramework.dll bin\SlimDX\
rem copy SlimDX\AllBulletDemos\bin\Release\AllBulletDemos.exe bin\SlimDX\
copy SlimDX\BasicDemo\bin\x86\Release\BasicDemo.exe bin\SlimDX\
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
