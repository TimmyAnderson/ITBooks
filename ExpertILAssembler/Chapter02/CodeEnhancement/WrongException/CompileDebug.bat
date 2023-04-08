del WrongException.exe
del WrongException.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:WrongException.exe /DEBUG WrongException.il 2>Errors.txt