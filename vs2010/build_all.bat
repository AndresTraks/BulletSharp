@echo off
set MSBUILD=%WINDIR%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe

set VCPATH="[%PROGRAMFILES^(x86^)%]"
if %VCPATH%=="[]" set VCPATH=%PROGRAMFILES%
set VCPATH="%VCPATH%\Microsoft Visual Studio 10.0\VC\vcpackages"

set OPTS=BulletSharp.vcxproj /p:VCBuildToolPath=%VCPATH%

%MSBUILD% %OPTS% /p:Configuration="Release Axiom"
%MSBUILD% %OPTS% /p:Configuration="Release Mogre"
%MSBUILD% %OPTS% /p:Configuration="Release NoGfx"
%MSBUILD% %OPTS% /p:Configuration="Release OpenTK"
%MSBUILD% %OPTS% /p:Configuration="Release SharpDX"
%MSBUILD% %OPTS% /p:Configuration="Release SlimDX"
%MSBUILD% %OPTS% /p:Configuration="Release XNA 3.1"
%MSBUILD% %OPTS% /p:Configuration="Release XNA 4.0"
%MSBUILD% %OPTS% /p:Configuration="Release SlimMath"
