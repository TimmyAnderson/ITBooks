del SimpleSampleCodeDirectives.exe
del SimpleSampleCodeDirectives.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleSampleCodeDirectives.exe /DEBUG SimpleSampleCodeDirectives.il 2>Errors.txt