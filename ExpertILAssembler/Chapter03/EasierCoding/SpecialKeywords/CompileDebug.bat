del SpecialKeywords.exe
del SpecialKeywords.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SpecialKeywords.exe /DEBUG SpecialKeywords.il 2>Errors.txt