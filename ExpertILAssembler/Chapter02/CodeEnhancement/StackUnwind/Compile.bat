del StackUnwind.exe
del StackUnwind.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:StackUnwind.exe StackUnwind.il 2>Errors.txt