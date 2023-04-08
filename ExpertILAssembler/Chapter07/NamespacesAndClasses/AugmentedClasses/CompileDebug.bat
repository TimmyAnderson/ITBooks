del AugmentedClasses.exe
del AugmentedClasses.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:AugmentedClasses.exe /DEBUG AugmentedClasses.il 2>Errors.txt