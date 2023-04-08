del IndirectCalls.exe
del IndirectCalls.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:IndirectCalls.exe /DEBUG IndirectCalls.il 2>Errors.txt