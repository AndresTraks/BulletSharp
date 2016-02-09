@echo off
set MSBUILD=%WINDIR%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe

if "[%ProgramFiles(x86)%]"=="[]" goto x86
set VCPATH=%ProgramFiles(x86)%
goto checkdone
:x86
set VCPATH=%ProgramFiles%
:checkdone

set VCPATH="%VCPATH%\Microsoft Visual Studio 12.0\VC\vcpackages"
set OPTS=BulletSharp.vcxproj /p:VCBuildToolPath=%VCPATH% /p:VisualStudioVersion=12.0
rem set OPTS=%OPTS% /p:Platform=x64

%MSBUILD% %OPTS% /p:Configuration="Release Generic"
%MSBUILD% %OPTS% /p:Configuration="Release Mogre"
%MSBUILD% %OPTS% /p:Configuration="Release MonoGame"
%MSBUILD% %OPTS% /p:Configuration="Release OpenTK"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX Signed"
%MSBUILD% %OPTS% /p:Configuration="Release SlimDX"
