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

copy "..\Release NoGfx\BulletSharp.dll" bin\


copy Generic\bin\Release\DemoFramework.dll bin\
copy Generic\bin\Release\DemoFramework.OpenTK.dll bin\
copy Generic\bin\Release\DemoFramework.SharpDX.dll bin\
copy Generic\bin\Release\DemoFramework.SlimDX.dll bin\
copy Generic\bin\Release\DemoFramework.Xna.dll bin\
copy Generic\bin\Release\BasicDemo.exe bin\
copy Generic\bin\Release\BenchmarkDemo.exe bin\
copy Generic\bin\Release\Box2DDemo.exe bin\
copy Generic\bin\Release\BspDemo.exe bin\
copy Generic\bin\Release\CcdPhysicsDemo.exe bin\
copy Generic\bin\Release\ConstraintDemo.exe bin\
copy Generic\bin\Release\ConvexDecompositionDemo.exe bin\
copy Generic\bin\Release\SoftDemo.exe bin\
copy Generic\bin\Release\BspDemo.bsp bin\
copy Generic\bin\Release\file.obj bin\

copy Generic\bin\Release\OpenTK.dll bin\
copy Generic\bin\Release\OpenTK.GLControl.dll bin\
copy Generic\bin\Release\SharpDX.dll bin\
copy Generic\bin\Release\SharpDX.D3DCompiler.dll bin\
copy Generic\bin\Release\SharpDX.Direct3D10.dll bin\
copy Generic\bin\Release\SharpDX.DXGI.dll bin\
copy Generic\bin\Release\fp.cg bin\
copy Generic\bin\Release\vp.cg bin\
copy Generic\bin\Release\grender.fx bin\
copy Generic\bin\Release\shader.fx bin\

cmd /C svn export http://bulletsharp.googlecode.com/svn/trunk/demos/Generic src --force

"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp-demos.7z bin src
"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp-demos.zip bin src
