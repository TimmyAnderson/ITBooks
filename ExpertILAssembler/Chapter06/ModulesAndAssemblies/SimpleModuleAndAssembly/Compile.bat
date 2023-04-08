del SimpleModuleAndAssembly.exe
del SimpleModuleAndAssembly.pdb
del Errors.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /KEY=MyKey.key /OUTPUT:SimpleModuleAndAssembly.exe SimpleModuleAndAssembly.il 2>Errors.txt