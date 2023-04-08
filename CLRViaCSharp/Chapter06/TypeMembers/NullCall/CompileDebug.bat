del NullCall.exe
del NullCall.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:NullCall.exe /DEBUG NullCall.il 2>Errors.txt