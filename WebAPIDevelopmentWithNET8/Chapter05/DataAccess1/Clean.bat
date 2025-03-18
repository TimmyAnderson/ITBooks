rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q DataAccess1\bin
rmdir /S /Q DataAccess1\obj

del /Q DataAccess1\MyDatabase.db
del /Q DataAccess1\MyDatabase.db-shm
del /Q DataAccess1\MyDatabase.db-wal

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q DataAccess1Web\bin
rmdir /S /Q DataAccess1Web\obj

del /Q DataAccess1Web\MyDatabase.db
del /Q DataAccess1Web\MyDatabase.db-shm
del /Q DataAccess1Web\MyDatabase.db-wal

del /Q DataAccess1.slnLaunch.user

rmdir /S /Q .vs