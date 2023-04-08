del Module1.mod
del Module2.mod
del Program.mod
del MultiModuleAssembly.exe
del Module1.pdb
del Module2.pdb
del Program.pdb
del MultiModuleAssembly.pdb
del Errors1.txt
del Errors2.txt
del Errors3.txt

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Module1.mod Module1.il
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Module2.mod Module2.il
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Program.mod Program.il

"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.0A\bin\NETFX 4.0 Tools\x64\al.exe" /out:MultiModuleAssembly.exe /target:exe /main:Exec /platform:x64 Module1.mod Module2.mod Program.mod