del ManagedDLL.dll
del ManagedDLL.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /PE64 /X64 /DLL /OUTPUT:ManagedDLL.dll ManagedDLL.il 2>Errors.txt