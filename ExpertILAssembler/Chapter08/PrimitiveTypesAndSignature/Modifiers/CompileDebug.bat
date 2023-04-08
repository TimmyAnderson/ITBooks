del Modifiers.exe
del Modifiers.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Modifiers.exe /DEBUG Modifiers.il 2>Errors.txt