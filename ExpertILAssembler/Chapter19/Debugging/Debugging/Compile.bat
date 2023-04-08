del Debugging.exe
del Debugging.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Debugging.exe Debugging.il 2>Errors.txt