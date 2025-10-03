rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q Testing1\bin
rmdir /S /Q Testing1\obj

del /Q Testing1\MyDatabase.db
del /Q Testing1\MyDatabase.db-shm
del /Q Testing1\MyDatabase.db-wal

rmdir /S /Q TestProject1_Tests\bin
rmdir /S /Q TestProject1_Tests\obj

del /Q Testing1.slnLaunch.user

rmdir /S /Q .vs