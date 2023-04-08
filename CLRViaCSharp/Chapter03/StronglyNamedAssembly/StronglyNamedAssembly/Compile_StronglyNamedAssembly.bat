rem Kompilacia DLL.
csc.exe /out:MyAssembly_StronglyNamedAssembly.dll /keyfile:MyFullKey.snk /target:library /r:MSCorLib.dll MyAssembly.cs

rem Kompilacia EXE.
csc.exe /out:Program_StronglyNamedAssembly.exe /keyfile:MyFullKey.snk /target:exe /r:MSCorLib.dll;MyAssembly_StronglyNamedAssembly.dll Program.cs