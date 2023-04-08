del TestAssembly.exe
del TestAssembly.pdb
del Errors.txt
del GeneratedCode.il
del GeneratedCode.exe

rem Vykona sa kompilacia povodnej ASSEMBLY.
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:TestAssembly.exe TestAssembly.il 2>Errors.txt

rem Z ASSEMBLY sa vygeneruje spatne MSIL CODE.
"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\x64\ildasm.exe" TestAssembly.exe /OUT:GeneratedCode.il

rem Vykona sa kompilacia novej ASSEMBLY.
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:GeneratedCode.exe GeneratedCode.il 2>Errors.txt