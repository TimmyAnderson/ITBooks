rem Kompilacia DLL.
csc.exe /out:MyAssembly_WeaklyNamedAssembly.dll /target:library /r:MSCorLib.dll MyAssembly.cs

rem Kompilacia EXE.
csc.exe /out:Program_WeaklyNamedAssembly.exe /target:exe /r:MSCorLib.dll;MyAssembly_WeaklyNamedAssembly.dll Program.cs