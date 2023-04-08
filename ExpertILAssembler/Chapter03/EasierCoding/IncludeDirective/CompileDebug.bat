del IncludeDirective.exe
del IncludeDirective.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:IncludeDirective.exe /DEBUG IncludeDirective.il 2>Errors.txt