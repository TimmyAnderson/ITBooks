del SimpleSample.exe
del SimpleSample.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleSample.exe SimpleSample.il 2>Errors.txt