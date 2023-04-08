del ClassesAndValueTypesInSignatures.exe
del ClassesAndValueTypesInSignatures.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:ClassesAndValueTypesInSignatures.exe ClassesAndValueTypesInSignatures.il 2>Errors.txt