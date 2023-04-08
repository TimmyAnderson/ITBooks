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

C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Module1.mod /DEBUG Module1.il 2>Errors1.txt
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Module2.mod /DEBUG Module2.il 2>Errors2.txt
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /DLL /OUTPUT:Program.mod /DEBUG Program.il 2>Errors3.txt

"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.0A\bin\NETFX 4.0 Tools\x64\al.exe" /out:MultiModuleAssembly.exe /target:exe /main:Exec /platform:x64 Module1.mod Module2.mod Program.mod