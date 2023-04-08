del Delegates.exe
del Delegates.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Delegates.exe Delegates.il 2>Errors.txt