del Methods.exe
del Methods.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Methods.exe Methods.il 2>Errors.txt