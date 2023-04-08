del UnmanagedCode.exe
del UnmanagedCode.pdb
del Errors.txt
del UnmanagedCOMServer.dll

"C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\x64\TlbImp.exe" UnmanagedCOMServer.tlb /out:UnmanagedCOMServer.dll /machine:X64
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm /X64 /EXE /OUTPUT:UnmanagedCode.exe /DEBUG UnmanagedCode.il 2>Errors.txt