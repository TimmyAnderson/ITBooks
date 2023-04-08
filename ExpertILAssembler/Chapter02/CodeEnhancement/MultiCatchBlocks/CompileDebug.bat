del MultiCatchBlocks.exe
del MultiCatchBlocks.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:MultiCatchBlocks.exe /DEBUG MultiCatchBlocks.il 2>Errors.txt