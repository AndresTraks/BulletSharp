@echo off

if "[%ProgramFiles(x86)%]"=="[]" goto x86
set PROGFILES=%ProgramFiles(x86)%
goto checkdone
:x86
set PROGFILES=%ProgramFiles%
:checkdone

set MSBUILD="%PROGFILES%\MSBuild\14.0\Bin\MSBuild.exe"

set VCPATH="%PROGFILES%\Microsoft Visual Studio 14.0\VC\vcpackages"
set OPTS=BulletSharp.vcxproj /p:VCBuildToolPath=%VCPATH% /p:VisualStudioVersion=14.0
rem set OPTS=%OPTS% /p:Platform=x64

set CONF=Release

%MSBUILD% %OPTS% /p:Configuration="%CONF% Generic"
%MSBUILD% %OPTS% /p:Configuration="%CONF% Mogre"
%MSBUILD% %OPTS% /p:Configuration="%CONF% MonoGame"
%MSBUILD% %OPTS% /p:Configuration="%CONF% Numerics"
%MSBUILD% %OPTS% /p:Configuration="%CONF% OpenTK"
%MSBUILD% %OPTS% /p:Configuration="%CONF% SharpDX"
