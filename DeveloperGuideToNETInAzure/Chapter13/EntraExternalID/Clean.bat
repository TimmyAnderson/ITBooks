rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q EntraExternalIDWebAPI\bin
rmdir /S /Q EntraExternalIDWebAPI\obj

rmdir /S /Q EntraExternalIDWebPages\bin
rmdir /S /Q EntraExternalIDWebPages\obj

del /Q EntraExternalIDWebAPI\MyDatabase.db
del /Q EntraExternalIDWebAPI\MyDatabase.db-shm
del /Q EntraExternalIDWebAPI\MyDatabase.db-wal

del /Q EntraExternalID.slnLaunch.user

rmdir /S /Q .vs