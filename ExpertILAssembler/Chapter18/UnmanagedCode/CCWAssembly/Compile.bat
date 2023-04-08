del CCWAssembly.dll
del CCWAssembly.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:CCWAssembly.dll /KEY=MyKeyPair.snk CCWAssembly.il 2>Errors.txt