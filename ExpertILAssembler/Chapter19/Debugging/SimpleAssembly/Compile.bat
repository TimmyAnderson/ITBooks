del SimpleAssembly.dll
del SimpleAssembly.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:SimpleAssembly.dll SimpleAssembly.il 2>Errors.txt