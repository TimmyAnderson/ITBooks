del EventsAndProperties.exe
del EventsAndProperties.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:EventsAndProperties.exe EventsAndProperties.il 2>Errors.txt