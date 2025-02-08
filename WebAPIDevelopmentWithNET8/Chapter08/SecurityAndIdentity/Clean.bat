rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q SecurityAndIdentity\bin
rmdir /S /Q SecurityAndIdentity\obj

del /Q SecurityAndIdentity\MyIdentityDatabase.db

del /Q SecurityAndIdentity.slnLaunch.user

rmdir /S /Q .vs