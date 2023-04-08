del Namespaces.exe
del Namespaces.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Namespaces.exe /DEBUG Namespaces.il 2>Errors.txt