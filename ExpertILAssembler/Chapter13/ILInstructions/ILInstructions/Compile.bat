del ILInstructions.exe
del ILInstructions.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:ILInstructions.exe ILInstructions.il 2>Errors.txt