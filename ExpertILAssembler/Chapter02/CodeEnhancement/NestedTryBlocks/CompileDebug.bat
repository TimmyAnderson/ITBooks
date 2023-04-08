del NestedTryBlocks.exe
del NestedTryBlocks.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:NestedTryBlocks.exe /DEBUG NestedTryBlocks.il 2>Errors.txt