rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q Testing2\bin
rmdir /S /Q Testing2\obj

del /Q Testing2\MyDatabase.db
del /Q Testing2\MyDatabase.db-shm
del /Q Testing2\MyDatabase.db-wal

rmdir /S /Q TestProject2_Tests\bin
rmdir /S /Q TestProject2_Tests\obj
rmdir /S /Q TestProject2_Tests\TestResults

rmdir /S /Q CoverageReport

del /Q coverage.json

del /Q Testing2.slnLaunch.user

rmdir /S /Q .vs