rmdir /S /Q Client1\bin
rmdir /S /Q Client1\obj

rmdir /S /Q Client2\bin
rmdir /S /Q Client2\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q UsingSignalR\bin
rmdir /S /Q UsingSignalR\obj

del /Q UsingSignalR\MyDatabase.db
del /Q UsingSignalR\MyDatabase.db-shm
del /Q UsingSignalR\MyDatabase.db-wal

del /Q UsingSignalR.slnLaunch.user

rmdir /S /Q .vs