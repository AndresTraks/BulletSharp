@echo off

if "[%ProgramFiles(x86)%]"=="[]" goto x86
set PROGFILES=%ProgramFiles(x86)%
set MSBUILD="%PROGFILES%\MSBuild\14.0\Bin\amd64\MSBuild.exe"
goto checkdone
:x86
set PROGFILES=%ProgramFiles%
set MSBUILD="%PROGFILES%\MSBuild\14.0\Bin\MSBuild.exe"
:checkdone

set VCPATH="%PROGFILES%\Microsoft Visual Studio 14.0\VC\vcpackages"
set OPTS=BulletSharp.vcxproj /p:VCBuildToolPath=%VCPATH% /p:VisualStudioVersion=14.0

%MSBUILD% %OPTS% /p:Configuration="Release Axiom"
%MSBUILD% %OPTS% /p:Configuration="Release Generic"
%MSBUILD% %OPTS% /p:Configuration="Release Mogre"
%MSBUILD% %OPTS% /p:Configuration="Release OpenTK"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX Signed"
%MSBUILD% %OPTS% /p:Configuration="Release SlimDX"
%MSBUILD% %OPTS% /p:Configuration="Release MonoGame"
%MSBUILD% %OPTS% /p:Configuration="Release Windows API Code Pack"
