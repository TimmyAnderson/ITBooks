rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q MyAzureFunctions\bin
rmdir /S /Q MyAzureFunctions\obj
rmdir /S /Q MyAzureFunctions\Deploy

rmdir /S /Q MyDurableAzureFunctions\bin
rmdir /S /Q MyDurableAzureFunctions\obj

rmdir /S /Q MyContainerApps\bin
rmdir /S /Q MyContainerApps\obj

del /Q AzureFunctionsAndContainerApps.slnLaunch.user

rmdir /S /Q .vs