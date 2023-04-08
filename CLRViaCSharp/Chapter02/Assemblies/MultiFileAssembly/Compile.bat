csc.exe /out:Module1.netmodule /target:module /r:MSCorLib.dll Module1.cs
csc.exe /out:Module2.netmodule /target:module /r:MSCorLib.dll Module2.cs

csc.exe /out:Program.exe /target:exe /r:MSCorLib.dll /addmodule:Module1.netmodule;Module2.netmodule Program.cs