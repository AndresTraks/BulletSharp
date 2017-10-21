if (-not (Get-Module -ListAvailable VSSetup)) {
	Write-Host "Installing VSSetup module"
	Install-Module VSSetup -Scope CurrentUser
}

$conf = "Release"
$targetLibs = @("Generic", "Mogre", "MonoGame", "Numerics", "OpenTK", "SharpDX")


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
Write-Host "MSBuild path: $msBuild"

$project = "BulletSharp.vcxproj"

$vcPath = "%PROGFILES%\Microsoft Visual Studio 15.0\VC\vcpackages"
$opts = "/p:VCBuildToolPath=$vcPath /p:VisualStudioVersion=15.0 $project"

foreach ($lib in $targetLibs) {
	#iex '& "$msBuild" $opts /p:Platform=x64 /p:Configuration="$conf $lib"'
	iex '& "$msBuild" $opts /p:Configuration="$conf $lib"'
}


$szip = "$env:programfiles\7-Zip\7z.exe"
if (test-path $szip) {
	set-alias 7z $szip
	$binaries = ($targetLibs | foreach { """$conf $_\BulletSharp.dll"""})
    #7z a bulletsharp.7z $binaries
    7z a bulletsharp.zip $binaries
} else {
	Write-Host "7-zip not found, skipping packaging"
}
