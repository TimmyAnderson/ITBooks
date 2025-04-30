rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q DataAccess3\bin
rmdir /S /Q DataAccess3\obj

del /Q DataAccess3\MyDatabase.db
del /Q DataAccess3\MyDatabase.db-shm
del /Q DataAccess3\MyDatabase.db-wal

rmdir /S /Q DataAccess3SqlServer\bin
rmdir /S /Q DataAccess3SqlServer\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q DataAccess3Web\bin
rmdir /S /Q DataAccess3Web\obj

del /Q DataAccess3Web\MyDatabase1.db
del /Q DataAccess3Web\MyDatabase1.db-shm
del /Q DataAccess3Web\MyDatabase1.db-wal

del /Q DataAccess3Web\MyDatabase2.db
del /Q DataAccess3Web\MyDatabase2.db-shm
del /Q DataAccess3Web\MyDatabase2.db-wal

del /Q DataAccess3.slnLaunch.user

rmdir /S /Q .vs