del SimpleSampleStrings.exe
del SimpleSampleStrings.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleSampleStrings.exe SimpleSampleStrings.il 2>Errors.txt