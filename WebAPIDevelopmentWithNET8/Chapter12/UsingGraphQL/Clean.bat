rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q UsingGraphQL\bin
rmdir /S /Q UsingGraphQL\obj

del /Q UsingGraphQL\MyDatabase.db
del /Q UsingGraphQL\MyDatabase.db-shm
del /Q UsingGraphQL\MyDatabase.db-wal

del /Q UsingGraphQL.slnLaunch.user

rmdir /S /Q .vs