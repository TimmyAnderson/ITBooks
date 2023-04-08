del ExceptionHandling.exe
del ExceptionHandling.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:ExceptionHandling.exe /DEBUG ExceptionHandling.il 2>Errors.txt