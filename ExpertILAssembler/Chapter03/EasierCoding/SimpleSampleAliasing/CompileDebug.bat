del SimpleSampleAliasing.exe
del SimpleSampleAliasing.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleSampleAliasing.exe /DEBUG SimpleSampleAliasing.il 2>Errors.txt