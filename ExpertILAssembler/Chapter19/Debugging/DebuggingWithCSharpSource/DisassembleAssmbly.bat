del NewAssembly.exe
del NewAssembly.pdb
del CSharpAssemblyAsILCode.il
del CSharpAssemblyAsILCode.res
del Errors.txt

rem Z ASSEMBLY sa vygeneruje spatne MSIL CODE.
"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\x64\ildasm.exe" SouceAssembly\CSharpAssembly.exe /SOURCE:SouceAssembly\Program.cs /OUT:CSharpAssemblyAsILCode.il

rem Vykona sa DEBUG kompilacia novej ASSEMBLY.
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /DEBUG /OUTPUT:NewAssembly.exe /RES:CSharpAssemblyAsILCode.res CSharpAssemblyAsILCode.il 2>Errors.txt