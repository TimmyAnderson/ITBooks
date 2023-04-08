del Names.exe
del Names.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Names.exe /DEBUG Names.il 2>Errors.txt