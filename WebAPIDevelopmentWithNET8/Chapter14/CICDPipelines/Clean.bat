rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q CICDPipelines\bin
rmdir /S /Q CICDPipelines\obj

rmdir /S /Q Azure\MyAzureProgram\bin
rmdir /S /Q Azure\MyAzureProgram\obj

rmdir /S /Q Azure\MyAzureProgramTests\bin
rmdir /S /Q Azure\MyAzureProgramTests\obj

del /Q CICDPipelines.slnLaunch.user

rmdir /S /Q .vs
rmdir /S /Q Azure\.vs