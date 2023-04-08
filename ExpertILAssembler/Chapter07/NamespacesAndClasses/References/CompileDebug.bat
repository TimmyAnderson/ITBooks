del Module.mod
del References.exe
del Module.pdb
del References.pdb
del Errors1.txt
del Errors2.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Module.mod /DEBUG Module.il 2>Errors1.txt
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:References.exe /DEBUG Program.il 2>Errors2.txt