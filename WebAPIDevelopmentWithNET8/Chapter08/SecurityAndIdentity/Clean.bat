rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q SecurityAndIdentity\bin
rmdir /S /Q SecurityAndIdentity\obj

del /Q SecurityAndIdentity\MyIdentityDatabase.db
del /Q SecurityAndIdentity\MyIdentityDatabase.db-shm
del /Q SecurityAndIdentity\MyIdentityDatabase.db-wal

rmdir /S /Q NewIdentityAPI\bin
rmdir /S /Q NewIdentityAPI\obj

del /Q NewIdentityAPI\MyIdentityDatabase.db
del /Q NewIdentityAPI\MyIdentityDatabase.db-shm
del /Q NewIdentityAPI\MyIdentityDatabase.db-wal

del /Q SecurityAndIdentity.slnLaunch.user

rmdir /S /Q .vs