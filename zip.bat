set FILES="Release SlimDX\bulletsharp.dll" "Release Generic\bulletsharp.dll" "Release Numerics\bulletsharp.dll" "Release OpenTK\bulletsharp.dll" "Release SharpDX\bulletsharp.dll" "Release Mogre\bulletsharp.dll" "Release MonoGame\bulletsharp.dll"

"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp.7z %FILES%
"%PROGRAMFILES%\7-Zip\7z.exe" a bulletsharp.zip %FILES%
