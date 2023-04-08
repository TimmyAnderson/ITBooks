del Fields.exe
del Fields.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Fields.exe /DEBUG Fields.il 2>Errors.txt