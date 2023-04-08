del SimpleSampleExceptions.exe
del SimpleSampleExceptions.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleSampleExceptions.exe SimpleSampleExceptions.il 2>Errors.txt