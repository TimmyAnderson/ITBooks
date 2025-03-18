rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q DataAccess2\bin
rmdir /S /Q DataAccess2\obj

del /Q DataAccess2\MyDatabase.db
del /Q DataAccess2\MyDatabase.db-shm
del /Q DataAccess2\MyDatabase.db-wal

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q DataAccess2Web\bin
rmdir /S /Q DataAccess2Web\obj

del /Q DataAccess2Web\MyDatabase.db
del /Q DataAccess2Web\MyDatabase.db-shm
del /Q DataAccess2Web\MyDatabase.db-wal

del /Q DataAccess2.slnLaunch.user

rmdir /S /Q .vs