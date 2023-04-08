del GenericTypes.exe
del GenericTypes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:GenericTypes.exe GenericTypes.il 2>Errors.txt