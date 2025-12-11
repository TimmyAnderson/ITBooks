rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q CqrsClient\bin
rmdir /S /Q CqrsClient\obj

rmdir /S /Q CqrsCore\bin
rmdir /S /Q CqrsCore\obj

rmdir /S /Q CqrsInfrastructure\bin
rmdir /S /Q CqrsInfrastructure\obj

rmdir /S /Q CqrsWeb\bin
rmdir /S /Q CqrsWeb\obj

del /Q CqrsWeb\MyDatabase.db
del /Q CqrsWeb\MyDatabase.db-shm
del /Q CqrsWeb\MyDatabase.db-wal

rmdir /S /Q PollyClient\bin
rmdir /S /Q PollyClient\obj

rmdir /S /Q PollyClientWeb\bin
rmdir /S /Q PollyClientWeb\obj

rmdir /S /Q PollyServerWeb\bin
rmdir /S /Q PollyServerWeb\obj

del /Q CloudNativePatterns.slnLaunch.user

rmdir /S /Q .vs