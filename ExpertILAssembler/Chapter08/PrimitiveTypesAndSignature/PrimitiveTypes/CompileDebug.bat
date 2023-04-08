del PrimitiveTypes.exe
del PrimitiveTypes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:PrimitiveTypes.exe /DEBUG PrimitiveTypes.il 2>Errors.txt