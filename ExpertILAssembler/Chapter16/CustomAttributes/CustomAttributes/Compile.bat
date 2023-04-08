del CustomAttributes.exe
del CustomAttributes.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:CustomAttributes.exe CustomAttributes.il 2>Errors.txt