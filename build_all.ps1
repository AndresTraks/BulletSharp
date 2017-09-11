# Install the Visual Studio Setup PowerShell Module like so:
#Install-Module VSSetup -Scope CurrentUser

$vs = Get-VSSetupInstance -All | Select-VSSetupInstance -Require 'Microsoft.VisualStudio.Workload.ManagedDesktop' -Latest

if ([System.IntPtr]::Size -eq 8)
{
	$msBuildPath = Join-Path $vs.InstallationPath "MSBuild\15.0\Bin\amd64"
}
else
{
	$msBuildPath = Join-Path $vs.InstallationPath "MSBuild\15.0\Bin"
}
$msBuild = Join-Path $msBuildPath "MSBuild.exe"

$project = "BulletSharp.vcxproj"

$vcPath = "%PROGFILES%\Microsoft Visual Studio 15.0\VC\vcpackages"
$opts = "/p:VCBuildToolPath=$vcPath /p:VisualStudioVersion=15.0 $project"

$conf = "Release"

iex '& "$msBuild" $opts /p:Configuration="$conf Generic"'