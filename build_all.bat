@echo off
set MSBUILD=%WINDIR%\Microsoft.NET\Framework\v2.0.50727\MSBuild.exe

set VCPATH="[%PROGRAMFILES^(x86^)%]"
if %VCPATH%=="[]" set VCPATH=%PROGRAMFILES%
set VCPATH="%VCPATH%\Microsoft Visual Studio 9.0\VC\vcpackages"

set OPTS=BulletSharp.vcproj /p:VCBuildToolPath=%VCPATH%

%MSBUILD% %OPTS% /p:Configuration="Release Axiom"
%MSBUILD% %OPTS% /p:Configuration="Release Mogre"
%MSBUILD% %OPTS% /p:Configuration="Release NoGfx"
%MSBUILD% %OPTS% /p:Configuration="Release OpenTK"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX"
%MSBUILD% %OPTS% /p:Configuration="Release SlimDX"
%MSBUILD% %OPTS% /p:Configuration="Release XNA 3.1"
