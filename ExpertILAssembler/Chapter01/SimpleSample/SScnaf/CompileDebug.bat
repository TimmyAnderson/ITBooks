del SScanf.exe
del SScanf.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SScanf.exe /DEBUG SScanf.il 2>Errors.txt