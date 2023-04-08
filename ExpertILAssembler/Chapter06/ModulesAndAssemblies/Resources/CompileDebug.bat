del SimpleXMLResource.resources
del Resources.exe
del Resources.pdb
del Errors.txt

"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.0A\bin\NETFX 4.0 Tools\ResGen.exe" SimpleXMLResource.resx
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:Resources.exe /DEBUG Resources.il 2>Errors.txt