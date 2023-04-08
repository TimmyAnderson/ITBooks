del GenericMethods.exe
del GenericMethods.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:GenericMethods.exe GenericMethods.il 2>Errors.txt