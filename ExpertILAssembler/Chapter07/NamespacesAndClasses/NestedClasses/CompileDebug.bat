del NestedClasses.exe
del NestedClasses.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:NestedClasses.exe /DEBUG NestedClasses.il 2>Errors.txt