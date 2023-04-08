del SecurityAttributes.exe
del SecurityAttributes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SecurityAttributes.exe SecurityAttributes.il 2>Errors.txt