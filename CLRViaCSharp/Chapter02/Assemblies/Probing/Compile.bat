mkdir SomeSubDirectory

csc.exe /out:MyAssembly.dll /target:library /r:MSCorLib.dll MyAssembly.cs

csc.exe /out:Program.exe /target:exe /r:MSCorLib.dll;MyAssembly.dll Program.cs

rem Presuniem MyAssembly.dll do podadresara aby sa MUSEL pouzit PRIVATE PATH PROBING.
move MyAssembly.dll SomeSubDirectory/