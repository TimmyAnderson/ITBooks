del SimpleNamespaceAndClass.exe
del SimpleNamespaceAndClass.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:SimpleNamespaceAndClass.exe /DEBUG SimpleNamespaceAndClass.il 2>Errors.txt