del ValueTypes.exe
del ValueTypes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:ValueTypes.exe /DEBUG ValueTypes.il 2>Errors.txt