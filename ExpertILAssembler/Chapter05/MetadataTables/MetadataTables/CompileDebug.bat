del MetadataTables.exe
del MetadataTables.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:MetadataTables.exe /DEBUG MetadataTables.il 2>Errors.txt