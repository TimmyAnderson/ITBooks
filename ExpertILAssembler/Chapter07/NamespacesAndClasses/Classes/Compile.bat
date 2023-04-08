del Classes.exe
del Classes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Classes.exe Classes.il 2>Errors.txt