del PrintException.exe
del PrintException.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:PrintException.exe PrintException.il 2>Errors.txt