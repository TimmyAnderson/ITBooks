rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MyWebProject\bin
rmdir /S /Q MyWebProject\obj

del /Q MyWebProject\MyDatabase.db
del /Q MyWebProject\MyDatabase.db-shm
del /Q MyWebProject\MyDatabase.db-wal

rmdir /S /Q RemoteWebService\bin
rmdir /S /Q RemoteWebService\obj

del /Q ErrorHandlingMonitoringAndObservability.slnLaunch.user

rmdir /S /Q .vs